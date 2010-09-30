#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Quaternion.h>
#include <ipc_bridge/msgs/geometry_msgs_Quaternion.h>

#define NAMESPACE geometry_msgs
#define NAME Quaternion

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.x = msg->x;
  out_msg.y = msg->y;
  out_msg.z = msg->z;
  out_msg.w = msg->w;

  p->Publish(out_msg);
}

#include "publisher.h"
