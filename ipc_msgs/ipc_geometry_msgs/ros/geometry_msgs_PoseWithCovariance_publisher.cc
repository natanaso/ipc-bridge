#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/PoseWithCovariance.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseWithCovariance.h>

#define NAMESPACE geometry_msgs
#define NAME PoseWithCovariance

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.pose.position.x = msg->pose.position.x;
  out_msg.pose.position.y = msg->pose.position.y;
  out_msg.pose.position.z = msg->pose.position.z;

  out_msg.pose.orientation.x = msg->pose.orientation.x;
  out_msg.pose.orientation.y = msg->pose.orientation.y;
  out_msg.pose.orientation.z = msg->pose.orientation.z;
  out_msg.pose.orientation.w = msg->pose.orientation.w;

  for (int i = 0; i < 36; i++)
    out_msg.covariance[i] = msg->covariance[i];

  p->Publish(out_msg);
}

#include "publisher.h"
