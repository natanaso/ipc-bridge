#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <vicon/Names.h>
#include <ipc_bridge/msgs/vicon_Names.h>

#define NAMESPACE vicon
#define NAME Names

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.names_length = msg->names.size();

  char *names[out_msg.names_length];
  
  for (unsigned int i = 0; i < out_msg.names_length; i++)
    {
      names[i] = new char[strlen(msg->names[i].c_str())+1];
      strcpy(names[i], msg->names[i].c_str());
    }
  out_msg.names = names;

  p->Publish(out_msg);

  for (unsigned int i = 0; i < out_msg.names_length; i++)
    delete[] out_msg.names[i];
  out_msg.names = 0;
}

#include "publisher.h"
