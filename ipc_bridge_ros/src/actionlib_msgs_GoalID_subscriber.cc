#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <actionlib_msgs/GoalID.h>
#include <ipc_bridge/msgs/actionlib_msgs_GoalID.h>

#define NAMESPACE actionlib_msgs
#define NAME GoalID

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.stamp = ros::Time(msg.stamp);
  if (msg.id != 0)
    out_msg.id = std::string(msg.id);
  else
    out_msg.id = std::string("");

  pub.publish(out_msg);
}

#include "subscriber.h"
