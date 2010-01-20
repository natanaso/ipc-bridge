#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <ipc_bridge/msgs/move_base_msgs_MoveBaseActionFeedback.h>

#define NAMESPACE move_base_msgs
#define NAME MoveBaseActionFeedback

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

  out_msg.status.goal_id.stamp = ros::Time(msg.status.goal_id.stamp);
  
  if (msg.status.goal_id.id != 0)
    out_msg.status.goal_id.id = std::string(msg.status.goal_id.id);
  else
    out_msg.status.goal_id.id = std::string("");
  out_msg.status.status = msg.status.status;
  if (msg.status.text != 0)
    out_msg.status.text = std::string(msg.status.text);
  else
    out_msg.status.text = std::string("");

  out_msg.feedback.base_position.header.seq = 
    msg.feedback.base_position.header.seq;
  out_msg.feedback.base_position.header.stamp = 
    ros::Time(msg.feedback.base_position.header.stamp);
  if (msg.feedback.base_position.header.frame_id != 0)
    out_msg.feedback.base_position.header.frame_id = 
      std::string(msg.feedback.base_position.header.frame_id);
  else
    out_msg.feedback.base_position.header.frame_id = std::string("");

  out_msg.feedback.base_position.pose.position.x =
    msg.feedback.base_position.pose.position.x;
  out_msg.feedback.base_position.pose.position.y =
    msg.feedback.base_position.pose.position.y;
  out_msg.feedback.base_position.pose.position.z =
    msg.feedback.base_position.pose.position.z;

  out_msg.feedback.base_position.pose.orientation.x =
    msg.feedback.base_position.pose.orientation.x;
  out_msg.feedback.base_position.pose.orientation.y =
    msg.feedback.base_position.pose.orientation.y;
  out_msg.feedback.base_position.pose.orientation.z =
    msg.feedback.base_position.pose.orientation.z;
  out_msg.feedback.base_position.pose.orientation.w =
    msg.feedback.base_position.pose.orientation.w;

  pub.publish(out_msg);
}

#include "subscriber.h"
