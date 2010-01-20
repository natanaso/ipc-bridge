#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <move_base_msgs/MoveBaseActionGoal.h>
#include <ipc_bridge/msgs/move_base_msgs_MoveBaseActionGoal.h>

#define NAMESPACE move_base_msgs
#define NAME MoveBaseActionGoal

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;
unsigned int goal_id_prior_size = 0;
unsigned int pose_id_prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_size)
    {
      if (out_msg.header.frame_id != 0)
        delete[] out_msg.header.frame_id;

      out_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());
      frame_id_prior_size = strlen(msg->header.frame_id.c_str());
    }

  out_msg.goal_id.stamp = msg->goal_id.stamp.toSec();
  if (strlen(msg->goal_id.id.c_str()) != goal_id_prior_size)
    {
      if (out_msg.goal_id.id != 0)
        delete[] out_msg.goal_id.id;

      out_msg.goal_id.id = 
        new char[strlen(msg->goal_id.id.c_str()) + 1];
      strcpy(out_msg.goal_id.id, msg->goal_id.id.c_str());
      goal_id_prior_size = strlen(msg->goal_id.id.c_str());
    }

  out_msg.goal.target_pose.header.seq = msg->goal.target_pose.header.seq;
  out_msg.goal.target_pose.header.stamp = 
    msg->goal.target_pose.header.stamp.toSec();
  if (strlen(msg->goal.target_pose.header.frame_id.c_str()) != pose_id_prior_size)
    {
      if (out_msg.goal.target_pose.header.frame_id != 0)
        delete[] out_msg.goal.target_pose.header.frame_id;

      out_msg.goal.target_pose.header.frame_id = 
        new char[strlen(msg->goal.target_pose.header.frame_id.c_str()) + 1];
      strcpy(out_msg.goal.target_pose.header.frame_id, 
             msg->goal.target_pose.header.frame_id.c_str());
      pose_id_prior_size = strlen(msg->goal.target_pose.header.frame_id.c_str());
    }

  out_msg.goal.target_pose.pose.position.x = 
    msg->goal.target_pose.pose.position.x;
  out_msg.goal.target_pose.pose.position.y = 
    msg->goal.target_pose.pose.position.y;
  out_msg.goal.target_pose.pose.position.z = 
    msg->goal.target_pose.pose.position.z;

  out_msg.goal.target_pose.pose.orientation.x = 
    msg->goal.target_pose.pose.orientation.x;
  out_msg.goal.target_pose.pose.orientation.y = 
    msg->goal.target_pose.pose.orientation.y;
  out_msg.goal.target_pose.pose.orientation.z = 
    msg->goal.target_pose.pose.orientation.z;
  out_msg.goal.target_pose.pose.orientation.w = 
    msg->goal.target_pose.pose.orientation.w;

  p->Publish(out_msg);
}

#include "publisher.h"
