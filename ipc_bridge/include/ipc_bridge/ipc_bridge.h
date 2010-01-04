#ifndef __IPC_BRIDGE__
#define __IPC_BRIDGE__
#include <ipc.h>
#include <string>
#include <sys/time.h>
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

      if (IPC_connect((const char*)module_name.c_str()) != IPC_OK)
        {
          printf("Failed to connect to %s\n", module_name.c_str());
          return -1;
        }

      if (IPC_isConnected() != 1)
        {
          printf("Failed to connect to module named %s\n", module_name.c_str());
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
      
      std::string message_format(T::getIPCFormat()); 
      
      IPC_defineMsg((const char*)message_name.c_str(), 
                    IPC_VARIABLE_LENGTH, 
                    (const char*)message_format.c_str());
      
      if (IPC_isMsgDefined((const char*)message_name.c_str()) != 1)
        {
          printf("Failed to define message %s\n", 
                 message_name.c_str());
          return -1;
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
        {
          printf("Failed to publish data of message name %s\n", 
                 message_name.c_str());      
        }
      
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
               void (*callback_ptr_)(const T&, void*) = 0,
               void *user_ptr_ = 0)
    {
      this->Initialize(module_name);
      message_name = message_name_;
      message_time = -1;
      
      callback_ptr = callback_ptr_;
      user_ptr = user_ptr_;

      memset((void*)&data, 0, sizeof(data));
      
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
      
      if (IPC_subscribe((const char*)message_name.c_str(),
                        Subscriber::IPCCallback,
                        (void*)this) != IPC_OK)
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
    
    void Listen(unsigned int timeout_ms = 1)
    {
      IPC_listen(timeout_ms);
      
      return;
    }

    void ListenClear(unsigned int timeout_ms = 1)
    {
      IPC_listenClear(timeout_ms);
      
      return;
    }

    T* GetData()
    {
      return &data;
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

    void MessageCallback()
    {
      if (callback_ptr != 0)
        (*callback_ptr)((const T&)data, user_ptr);

      return;
    }

  private:
    unsigned int GetDataSize()
    {
      return sizeof(data);
    }
    
    void* GetDataPtr()
    {
      return (void*)&data;
    }

    static void IPCCallback(MSG_INSTANCE msgInstance,
                            BYTE_ARRAY callData,
                            void* self)
    {
      Subscriber* r = reinterpret_cast<Subscriber*>(self);
      
      IPC_unmarshallData(IPC_msgInstanceFormatter(msgInstance), callData,
                         r->GetDataPtr(), r->GetDataSize());
      r->SetMessageTime();
      r->MessageCallback();
      
      return;
    }

    void (*callback_ptr)(const T&, void*);
    void *user_ptr;

    T data;    
    double message_time;
    
    bool subscribed;
    std::string message_name;
  };
}
#endif
