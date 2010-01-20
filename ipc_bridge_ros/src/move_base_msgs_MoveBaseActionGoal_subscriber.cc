#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <move_base_msgs/MoveBaseActionGoal.h>
#include <ipc_bridge/msgs/move_base_msgs_MoveBaseActionGoal.h>

#define NAMESPACE move_base_msgs
#define NAME MoveBaseActionGoal

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);
  if (msg.header.frame_id != 0)
    out_msg.header.frame_id = std::string(msg.header.frame_id);
  else
    out_msg.header.frame_id = std::string("");

  out_msg.goal_id.stamp = ros::Time(msg.goal_id.stamp);
  if (msg.goal_id.id != 0)
    out_msg.goal_id.id = std::string(msg.goal_id.id);
  else
    out_msg.goal_id.id = std::string("");

  out_msg.goal.target_pose.header.seq = 
    msg.goal.target_pose.header.seq;
  out_msg.goal.target_pose.header.stamp = 
    ros::Time(msg.goal.target_pose.header.stamp);
  if (msg.goal.target_pose.header.frame_id != 0)
    out_msg.goal.target_pose.header.frame_id = 
      std::string(msg.goal.target_pose.header.frame_id);
  else
    out_msg.goal.target_pose.header.frame_id = std::string("");

  out_msg.goal.target_pose.pose.position.x =
    msg.goal.target_pose.pose.position.x;
  out_msg.goal.target_pose.pose.position.y =
    msg.goal.target_pose.pose.position.y;
  out_msg.goal.target_pose.pose.position.z =
    msg.goal.target_pose.pose.position.z;

  out_msg.goal.target_pose.pose.orientation.x =
    msg.goal.target_pose.pose.orientation.x;
  out_msg.goal.target_pose.pose.orientation.y =
    msg.goal.target_pose.pose.orientation.y;
  out_msg.goal.target_pose.pose.orientation.z =
    msg.goal.target_pose.pose.orientation.z;
  out_msg.goal.target_pose.pose.orientation.w =
    msg.goal.target_pose.pose.orientation.w;

  pub.publish(out_msg);
}

#include "subscriber.h"
