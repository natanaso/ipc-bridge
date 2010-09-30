#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Twist.h>
#include <ipc_bridge/msgs/geometry_msgs_Twist.h>

#define NAMESPACE geometry_msgs
#define NAME Twist

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.linear.x = msg.linear.x;
  out_msg.linear.y = msg.linear.y;
  out_msg.linear.z = msg.linear.z;

  out_msg.angular.x = msg.angular.x;
  out_msg.angular.y = msg.angular.y;
  out_msg.angular.z = msg.angular.z;

  pub.publish(out_msg);
}

#include "subscriber.h"
