#ifndef __IPC_BRIDGE_MATLAB__
#define __IPC_BRIDGE_MATLAB__
#include <mex.h>
#include <map>
#include <list>

#include <ipc_bridge/ipc_bridge.h>

#define SUCCESS 0
#define EXIT -10
#define NOOVERWRITE -11
#define ERROR_INPUT -12
#define ERROR_UNHANDLED -14
#define ERROR_FAILED -15

#define MAX_QUEUE_SIZE 100

#define TRY(func, code) if (func != 0) {return code;}

namespace ipc_bridge_matlab
{ 
  static int GetDoubleArray(mxArray *in, const int length, double* out)
  {
    int nrows = mxGetM(in);
    int ncols = mxGetN(in);
    
    bool ok = false;
    if (nrows == length)
      if (ncols == 1)
        ok = true;
    
    if (ncols == length)
      if (nrows == 1)
        ok = true;
    
    if (!ok)
      {
        char buf[128];
        sprintf(buf, "Expected a %i x 1 or 1 x %i array, got %i x %i", 
                length, length, nrows, ncols);
        mexWarnMsgTxt(buf);
        return ERROR_FAILED;
      }
    
    double* p = mxGetPr(in);
    std::copy(p, p + length, out);    
   
    return SUCCESS;
  }
  
  template <typename T>
  class Interface
  {
  public:
    Interface(mxArray* (*message_handler_)(const T&), 
              int (*array_handler_)(const mxArray*, T&),
              void (*cleanup_handler_)(T&))
    {
      id_counter = 0;

      message_handler = message_handler_;
      array_handler = array_handler_;
      cleanup_handler = cleanup_handler_;
    }
    virtual ~Interface() 
    {
      Finalize();
    }

    static int CheckInput(int nrhs, int expected, const char *warn)
    {
      if (nrhs < expected)
        {
          char buf[128];
          sprintf(buf, "Bad %s Input", warn);
          mexWarnMsgTxt(buf);
          return -1;
        }
      return 0;
    }

    enum types {SCALAR, STRING};
    static int CheckInputType(const mxArray *in, types type)
    {
      bool ischar = false;
      if (mxIsChar(in))      
        ischar = true;
      
      switch (type)
        {
        case SCALAR:
          if (!ischar)
            return 0;
          mexWarnMsgTxt("Input Should be of type: Scalar");
          return -1;
        case STRING:
          if (ischar)
            return 0;
          mexWarnMsgTxt("Input Should be of type: String");
          return -1;
        default:
          return -1;
        }
      
      return ERROR_FAILED;
    }
    
    int ProcessCall(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
    {     
      TRY(CheckInput(nrhs, 1, "ProcessCall"), ERROR_INPUT);

      int buflen = 128;
      char buf[buflen];
      mxGetString(prhs[0], buf, buflen);

      if (!strcmp(buf, "read"))
        return Read(plhs, nrhs, prhs);
      else if (!strcmp(buf, "send"))
        return Send(nrhs, prhs);
      else if (!strcmp(buf, "connect"))
        return Connect(nrhs, prhs);
      else if (!strcmp(buf, "disconnect"))
        return Disconnect(nrhs, prhs);
      else if (!strcmp(buf, "empty"))
        return ReturnEmptyMessage(plhs);
      else
        {
          mexWarnMsgTxt("Unhandled Input.");
          return ERROR_UNHANDLED;
        }
      
      return ERROR_FAILED;
    }

    static void MessageCallback(const T &msg, void *user_ptr)
    {
      std::list<T> *msgs = reinterpret_cast<std::list<T>*>(user_ptr);

      msgs->push_back(msg);

      if (msgs->size() > MAX_QUEUE_SIZE)
        {
          mexWarnMsgTxt("Dropping older messages, queue is full!");
          msgs->pop_front();
        }

      return;
    }

    int Send(int nrhs, const mxArray *prhs[])
    {
      TRY(CheckInput(nrhs, 3, "send"), ERROR_INPUT);
      TRY(CheckInputType(prhs[1], SCALAR), ERROR_INPUT);

      unsigned int id = (unsigned int)mxGetScalar(prhs[1]);

      if (subscribers.count(id) > 0)
        {
          mexWarnMsgTxt("Attempted to send on a subscriber id");
          return ERROR_FAILED;
        }

      if (publishers.count(id) > 0)
        {
          if (array_handler(prhs[2], outgoing_msg) != SUCCESS)
            {
              mexWarnMsgTxt("Failed to populate outgoing message");
              return ERROR_FAILED;
            }

          publishers[id]->Publish(outgoing_msg);

          cleanup_handler(outgoing_msg);

          return SUCCESS;
        }

      return ERROR_FAILED;
    }

    int ReturnEmptyMessage(mxArray *plhs[])
    {
      T m;
      memset((void*)&m, 0, sizeof(m));
      plhs[0] = message_handler(m);

      return NOOVERWRITE;
    }

    typedef typename std::list<T>::iterator msg_iter;
    int Read(mxArray *plhs[], int nrhs, const mxArray *prhs[])
    {
      TRY(CheckInput(nrhs, 3, "read"), ERROR_INPUT);
      TRY(CheckInputType(prhs[1], SCALAR), ERROR_INPUT);
      TRY(CheckInputType(prhs[2], SCALAR), ERROR_INPUT);

      unsigned int id = (unsigned int)mxGetScalar(prhs[1]);
      unsigned int timeout = (unsigned int)mxGetScalar(prhs[2]);

      if (publishers.count(id) > 0)
        {
          mexWarnMsgTxt("Attempted to read on a publisher id");
          return ERROR_FAILED;
        }

      if (subscribers.count(id) > 0)
        {
          subscribers[id]->ListenClear(timeout);
          
          const int size = msgs[id]->size();
          plhs[0] = mxCreateCellArray(1, &size);

          unsigned int j = 0;
          for (msg_iter i = msgs[id]->begin(); i != msgs[id]->end(); ++i, j++)
            mxSetCell(plhs[0], j, message_handler(*i));
          
          msgs[id]->clear();

          return NOOVERWRITE;
        }

      mexWarnMsgTxt("Attempted to read on unknown id");
      if (id < id_counter)
        mexWarnMsgTxt("Did you call disconnect on this id?");
      else
        mexWarnMsgTxt("Did you call create yet to generate this id?");

      return ERROR_FAILED;
    }
    
    int Connect(int nrhs, const mxArray *prhs[])
    {
      TRY(CheckInput(nrhs, 4, "connect"), ERROR_INPUT);
      TRY(CheckInputType(prhs[1], STRING), ERROR_INPUT);
      TRY(CheckInputType(prhs[2], STRING), ERROR_INPUT);
      TRY(CheckInputType(prhs[3], STRING), ERROR_INPUT);
      
      int buflen = 128;
      char buf[buflen];

      mxGetString(prhs[1], buf, buflen);
      std::string type(buf);
      
      mxGetString(prhs[2], buf, buflen);
      std::string module_name(buf);
      
      mxGetString(prhs[3], buf, buflen);
      std::string message_name(buf);

      unsigned int id = id_counter;
      
      bool subscriber = false;

      if (type == std::string("subscriber"))
        {
          msgs[id] = new std::list<T>;
          ipc_bridge::Subscriber<T> *sub = new ipc_bridge::Subscriber<T>(module_name, message_name,
                                                                         Interface::MessageCallback,
                                                                         (void*)(msgs[id]));
          subscribers[id] = sub;
          id_counter++;
          subscriber = true;
        }
      else if (type == std::string("publisher"))
        {
          ipc_bridge::Publisher<T> *pub = new ipc_bridge::Publisher<T>(module_name, message_name);
          publishers[id] = pub;
          id_counter++;
          subscriber = false;
        }
      else
        {
          char buf[256];
          sprintf(buf, "Unrecognized type: %s. Choose 'subscriber' or 'publisher'.", 
                  type.c_str());
          mexWarnMsgTxt(buf);
          return ERROR_FAILED;
        }
      
      if (subscriber)
        {
          if (subscribers[id]->Connect() != 0)
            {
              char buf[256];
              sprintf(buf, "%s failed to connect subscriber to message %s", 
                      module_name.c_str(), message_name.c_str());
              mexWarnMsgTxt(buf);
              return ERROR_FAILED;
            }
        }
      else
        {
          if (publishers[id]->Connect() != 0)
            {
              char buf[256];
              sprintf(buf, "%s failed to connect publisher to message %s", 
                      module_name.c_str(), message_name.c_str());
              mexWarnMsgTxt(buf);
              return ERROR_FAILED;
            }
        }
      
      return id;
    }
    
    int Disconnect(int nrhs, const mxArray *prhs[])
    {
      TRY(CheckInput(nrhs, 2, "disconnect"), ERROR_INPUT);
      TRY(CheckInputType(prhs[1], SCALAR), ERROR_INPUT);

      unsigned int id = (unsigned int)mxGetScalar(prhs[1]);
      
      if (subscribers.count(id) > 0)
        {
          subscribers[id]->Disconnect();
          delete subscribers[id];
          subscribers.erase(id);
        }
      else if (publishers.count(id) > 0)
        {
          publishers[id]->Disconnect();
          delete publishers[id];
          publishers.erase(id);
        }
      else
        {
          mexWarnMsgTxt("Attempted to disconnect unknown id");
          return ERROR_FAILED;
        }
      
      return SUCCESS;
    }  

    void Finalize()
    {
      typedef typename std::map<unsigned int, ipc_bridge::Subscriber<T>*>::iterator s_iter;
      typedef typename std::map<unsigned int, ipc_bridge::Publisher<T>*>::iterator p_iter;
      typedef typename std::map<unsigned int, std::list<T>*>::iterator l_iter;

      for (s_iter i = subscribers.begin(); i != subscribers.end(); ++i)
        delete (*i).second;
      subscribers.clear();

      for (p_iter i = publishers.begin(); i != publishers.end(); ++i)
        delete (*i).second;
      publishers.clear();

      for (l_iter i = msgs.begin(); i != msgs.end(); ++i)
        delete (*i).second;
      msgs.clear();
    }
  private:
    std::map<unsigned int, ipc_bridge::Subscriber<T>*> subscribers;
    std::map<unsigned int, ipc_bridge::Publisher<T>*> publishers;
    std::map<unsigned int, std::list<T>*> msgs;

    T outgoing_msg;

    unsigned int id_counter;

    mxArray* (*message_handler)(const T&);
    int (*array_handler)(const mxArray*, T&);
    void (*cleanup_handler)(T&);
  };
}
#endif
