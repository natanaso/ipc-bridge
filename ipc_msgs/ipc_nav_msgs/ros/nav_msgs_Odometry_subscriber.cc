#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <nav_msgs/Odometry.h>
#include <ipc_bridge/msgs/nav_msgs_Odometry.h>

#define NAMESPACE nav_msgs
#define NAME Odometry

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);
  out_msg.header.frame_id = std::string(msg.header.frame_id);
  out_msg.child_frame_id = std::string(msg.child_frame_id);
  out_msg.pose.pose.position.x = msg.pose.pose.position.x;
  out_msg.pose.pose.position.y = msg.pose.pose.position.y;
  out_msg.pose.pose.position.z = msg.pose.pose.position.z;

  out_msg.pose.pose.orientation.x = msg.pose.pose.orientation.x;
  out_msg.pose.pose.orientation.y = msg.pose.pose.orientation.y;
  out_msg.pose.pose.orientation.z = msg.pose.pose.orientation.z;
  out_msg.pose.pose.orientation.w = msg.pose.pose.orientation.w;

  std::copy(msg.pose.covariance, msg.pose.covariance + 36,
            out_msg.pose.covariance.begin());

  out_msg.twist.twist.linear.x = msg.twist.twist.linear.x;
  out_msg.twist.twist.linear.y = msg.twist.twist.linear.y;
  out_msg.twist.twist.linear.z = msg.twist.twist.linear.z;

  out_msg.twist.twist.angular.x = msg.twist.twist.angular.x;
  out_msg.twist.twist.angular.y = msg.twist.twist.angular.y;
  out_msg.twist.twist.angular.z = msg.twist.twist.angular.z;

  std::copy(msg.twist.covariance, msg.twist.covariance + 36,
            out_msg.twist.covariance.begin());

  pub.publish(out_msg);
}

#include "subscriber.h"
