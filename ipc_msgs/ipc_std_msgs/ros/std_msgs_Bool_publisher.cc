#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <std_msgs/Bool.h>
#include <ipc_bridge/msgs/std_msgs_Bool.h>

#define NAMESPACE std_msgs
#define NAME Bool

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.data = (unsigned int)msg->data;
  p->Publish(out_msg);
}

#include "publisher.h"
