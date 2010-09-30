#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/PoseStamped.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseStamped.h>

#define NAMESPACE geometry_msgs
#define NAME PoseStamped

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{
  ROS_DEBUG("%s: receiving message", 
            ros::this_node::getName().c_str());

  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);
  if (msg.header.frame_id != 0)
    out_msg.header.frame_id = std::string(msg.header.frame_id);
  else
    out_msg.header.frame_id = std::string("");

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
