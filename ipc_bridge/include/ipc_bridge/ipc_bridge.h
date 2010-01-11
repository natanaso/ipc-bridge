#ifndef __IPC_BRIDGE__
#define __IPC_BRIDGE__
#include <ipc.h>
#include <string>
#include <sys/time.h>

#define MAX_QUEUE_LENGTH 10
#define IPC_CAPACITY 3

namespace ipc_bridge
{
  static double GetTimeDouble()
  {
    struct timeval ts;
    gettimeofday(&ts,0);
    return ts.tv_sec + ts.tv_usec/1e6;
  }

  class Interface
  {
  public:
    Interface()
    {
      connected = false;             
      
      return;
    }
    
    virtual ~Interface()
    {
      BaseDisconnect();
      
      return;
    }
    
    void Initialize(const std::string& module_name_)
    {
      module_name = module_name_;
    }
    
    int BaseConnect()
    {
      if (connected)
        {
          puts("Already connected");
          return 0;
        }

      if (IPC_setVerbosity(IPC_Silent) != IPC_OK)
        {
          printf("%s: Failed to set module verbosity level\n", module_name.c_str());
          return -1;         
        }

      if (IPC_connect((const char*)module_name.c_str()) != IPC_OK)
        {
          printf("%s: Failed to connect\n", module_name.c_str());
          return -1;
        }

      if (IPC_isConnected() != 1)
        {
          printf("%s: Failed to connect to module\n", module_name.c_str());
          return -1;
        }

      if (IPC_setCapacity(IPC_CAPACITY) != IPC_OK)
        {
          printf("%s: Failed to set IPC capacity\n", module_name.c_str());
          return -1;
        }
      
      connected = true;
      
      return 0;
    }
    
    void BaseDisconnect()
    {
      if (IPC_isConnected() == 1)
        IPC_disconnect();
      
      connected = false;
      
      return;
    }
    
    bool IsConnected()
    {
      return connected;
    }
    
  private:
    std::string module_name;
    
    bool connected;
  };
  
  template<typename T>
  class Publisher : public Interface
  {
  public:
    Publisher(const std::string& module_name, 
              const std::string& message_name_)
    {
      this->Initialize(module_name);
      message_name = message_name_;
    }

    virtual ~Publisher()
    {
      Disconnect();
      
      return;
    }
    
    int Connect()
    {
      if (this->BaseConnect() != 0)
        return -1;
                 
      if (IPC_isMsgDefined((const char*)message_name.c_str()) == 0)
        {
          std::string message_format(T::getIPCFormat()); 

          if (IPC_defineMsg((const char*)message_name.c_str(), 
                            IPC_VARIABLE_LENGTH, 
                            (const char*)message_format.c_str()) != IPC_OK)
            {
              printf("%s: Failed to define message\n", 
                     message_name.c_str());
              return -1;
            }
        }

      return 0;
    }
    
    void Disconnect()
    {
      this->BaseDisconnect();
    }
    
    void Publish(const T& data)
    {     
      if (this->IsConnected())
        IPC_publishData((const char*)message_name.c_str(), (void*)&data);
      else
        printf("%s: Failed to publish data\n", message_name.c_str());      
      
      return;
    }
    
  private:
    std::string message_name;
  };
  
  template<typename T>
  class Subscriber : public Interface
  {
  public:
    Subscriber(const std::string& module_name, 
               const std::string& message_name_,
               void (*callback_ptr_)(const T&) = 0)
      {
        this->Initialize(module_name);
        message_name = message_name_;
        message_time = -1;
        
        callback_ptr_1 = callback_ptr_;
        callback_ptr_2 = 0;
        callback_ptr_3 = 0;

        user_ptr = 0;

        subscribed = false;
      }

    Subscriber(const std::string& module_name, 
               const std::string& message_name_,
               void (*callback_ptr_)(const T&, double))
      {
        this->Initialize(module_name);
        message_name = message_name_;
        message_time = -1;

        callback_ptr_1 = 0;
        callback_ptr_2 = callback_ptr_;
        callback_ptr_3 = 0;
        
        user_ptr = 0;
        
        subscribed = false;
      }

    Subscriber(const std::string& module_name, 
               const std::string& message_name_,
               void (*callback_ptr_)(const T&, double, void*),
               void *user_ptr_)
      {
        this->Initialize(module_name);
        message_name = message_name_;
        message_time = -1;

        callback_ptr_1 = 0;
        callback_ptr_2 = 0;
        callback_ptr_3 = callback_ptr_;       

        user_ptr = user_ptr_;
        
        subscribed = false;
      }
    
    virtual ~Subscriber()
    {
      Disconnect();
      
      return;
    }
    
    int Connect()
    {
      if (this->BaseConnect() != 0)
        return -1;
      
      if (IPC_subscribeData((const char*)message_name.c_str(),
                            Subscriber::IPCCallback,
                            (void*)this) != IPC_OK)
        return -1;

      if (IPC_setMsgQueueLength((const char*)message_name.c_str(),
                                MAX_QUEUE_LENGTH) != IPC_OK)
        return -1;

      subscribed = true;

      return 0;
    }

    void Disconnect()
    {
      if (subscribed)
        {
          IPC_unsubscribe((const char*)message_name.c_str(),
                          Subscriber::IPCCallback);
          subscribed = false;
        }

      this->BaseDisconnect();
    }
    
    int Listen(unsigned int timeout_ms = 0)
    {
      if (IPC_listen(timeout_ms) != IPC_Timeout)
        return 0;
      
      return -1;
    }

    int ListenClear(unsigned int timeout_ms = 0)
    {
      if (IPC_listenClear(timeout_ms) != IPC_Timeout)
        return 0;
      
      return -1;
    }
        
    double GetMessageTime()
    {
      return message_time;
    }

    void SetMessageTime()
    {
      message_time = ipc_bridge::GetTimeDouble();
      return;
    }

    void MessageCallback(T* d)
    {
      if (callback_ptr_1 != 0)
        (*callback_ptr_1)((const T&)(*d));
      else if (callback_ptr_2 != 0)
        (*callback_ptr_2)((const T&)(*d), message_time);
      else if (callback_ptr_3 != 0)
        (*callback_ptr_3)((const T&)(*d), message_time, user_ptr);

      return;
    }

  private:
    static void IPCCallback(MSG_INSTANCE msgInstance,
                            void* callData,
                            void* self)
    {
      Subscriber* r = reinterpret_cast<Subscriber*>(self);
      r->SetMessageTime();
      r->MessageCallback(reinterpret_cast<T*>(callData));
      IPC_freeData(IPC_msgInstanceFormatter(msgInstance), callData);
    }

    void (*callback_ptr_1)(const T&);
    void (*callback_ptr_2)(const T&, double);
    void (*callback_ptr_3)(const T&, double, void*);
    void *user_ptr;

    double message_time;
    
    bool subscribed;
    std::string message_name;
  };
}
#endif
