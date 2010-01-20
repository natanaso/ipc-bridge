#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <actionlib_msgs/GoalID.h>
#include <ipc_bridge/msgs/actionlib_msgs_GoalID.h>

#define NAMESPACE actionlib_msgs
#define NAME GoalID

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int id_prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.stamp = msg->stamp.toSec();

  if (strlen(msg->id.c_str()) != id_prior_size)
    {
      if (out_msg.id != 0)
        delete[] out_msg.id;
      
      out_msg.id = 
        new char[strlen(msg->id.c_str()) + 1];
      strcpy(out_msg.id, msg->id.c_str());
      id_prior_size = strlen(msg->id.c_str());
    }

  p->Publish(out_msg);
}

#include "publisher.h"
