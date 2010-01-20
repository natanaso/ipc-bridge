#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <vicon/Subject.h>
#include <ipc_bridge/msgs/vicon_Subject.h>

#define NAMESPACE vicon
#define NAME Subject

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.name = std::string(msg.name);

  out_msg.pose.position.x = msg.pose.position.x;
  out_msg.pose.position.y = msg.pose.position.y;
  out_msg.pose.position.z = msg.pose.position.z;

  out_msg.pose.orientation.x = msg.pose.orientation.x;
  out_msg.pose.orientation.y = msg.pose.orientation.y;
  out_msg.pose.orientation.z = msg.pose.orientation.z;
  out_msg.pose.orientation.w = msg.pose.orientation.w;

  pub.publish(out_msg);
}

#include "subscriber.h"
