#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Pose.h>
#include <ipc_bridge/msgs/geometry_msgs_Pose.h>

#define NAMESPACE geometry_msgs
#define NAME Pose

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.position.x = msg->position.x;
  out_msg.position.y = msg->position.y;
  out_msg.position.z = msg->position.z;

  out_msg.orientation.x = msg->orientation.x;
  out_msg.orientation.y = msg->orientation.y;
  out_msg.orientation.z = msg->orientation.z;
  out_msg.orientation.w = msg->orientation.w;

  p->Publish(out_msg);
}

#include "publisher.h"
