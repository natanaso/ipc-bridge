#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <sensor_msgs/Image.h>
#include <ipc_bridge/msgs/sensor_msgs_Image.h>

#define NAMESPACE sensor_msgs
#define NAME Image

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);

  // TODO: Implement
  ROS_WARN("%s: not fully implemented", 
           ros::this_node::getName().c_str());

  pub.publish(out_msg);
}

#include "subscriber.h"
