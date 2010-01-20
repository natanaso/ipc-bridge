#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <ipc_bridge/msgs/move_base_msgs_MoveBaseActionFeedback.h>

#define NAMESPACE move_base_msgs
#define NAME MoveBaseActionFeedback

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;
unsigned int goal_id_prior_size = 0;
unsigned int text_prior_size = 0;
unsigned int base_prior_size = 0;

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

  out_msg.status.goal_id.stamp = msg->status.goal_id.stamp.toSec();
  if (strlen(msg->status.goal_id.id.c_str()) != goal_id_prior_size)
    {
      if (out_msg.status.goal_id.id != 0)
        delete[] out_msg.status.goal_id.id;

      out_msg.status.goal_id.id = 
        new char[strlen(msg->status.goal_id.id.c_str()) + 1];
      strcpy(out_msg.status.goal_id.id, msg->status.goal_id.id.c_str());
      goal_id_prior_size = strlen(msg->status.goal_id.id.c_str());
    }
  out_msg.status.status = msg->status.status;
  if (strlen(msg->status.text.c_str()) != text_prior_size)
    {
      if (out_msg.status.text != 0)
        delete[] out_msg.status.text;

      out_msg.status.text = 
        new char[strlen(msg->status.text.c_str()) + 1];
      strcpy(out_msg.status.text, msg->status.text.c_str());
      text_prior_size = strlen(msg->status.text.c_str());
    }
  
  out_msg.feedback.base_position.header.seq = 
    msg->feedback.base_position.header.seq;
  out_msg.feedback.base_position.header.stamp = 
    msg->feedback.base_position.header.stamp.toSec();
  if (strlen(msg->feedback.base_position.header.frame_id.c_str()) != base_prior_size)
    {
      if (out_msg.feedback.base_position.header.frame_id != 0)
        delete[] out_msg.feedback.base_position.header.frame_id;

      out_msg.feedback.base_position.header.frame_id = 
        new char[strlen(msg->feedback.base_position.header.frame_id.c_str()) + 1];
      strcpy(out_msg.feedback.base_position.header.frame_id, 
             msg->feedback.base_position.header.frame_id.c_str());
      base_prior_size = strlen(msg->feedback.base_position.header.frame_id.c_str());
    }

  out_msg.feedback.base_position.pose.position.x = 
    msg->feedback.base_position.pose.position.x;
  out_msg.feedback.base_position.pose.position.y = 
    msg->feedback.base_position.pose.position.y;
  out_msg.feedback.base_position.pose.position.z = 
    msg->feedback.base_position.pose.position.z;

  out_msg.feedback.base_position.pose.orientation.x = 
    msg->feedback.base_position.pose.orientation.x;
  out_msg.feedback.base_position.pose.orientation.y = 
    msg->feedback.base_position.pose.orientation.y;
  out_msg.feedback.base_position.pose.orientation.z = 
    msg->feedback.base_position.pose.orientation.z;
  out_msg.feedback.base_position.pose.orientation.w = 
    msg->feedback.base_position.pose.orientation.w;

  p->Publish(out_msg);
}

#include "publisher.h"
