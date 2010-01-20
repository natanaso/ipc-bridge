#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <actionlib_msgs/GoalStatusArray.h>
#include <ipc_bridge/msgs/actionlib_msgs_GoalStatusArray.h>

#define NAMESPACE actionlib_msgs
#define NAME GoalStatusArray

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;

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
  
  out_msg.status_list_length = msg->status_list.size();
  out_msg.status_list = 
    new actionlib_msgs_GoalStatus[out_msg.status_list_length];

  for (unsigned int i = 0; i < out_msg.status_list_length; i++)
    {
      out_msg.status_list[i].goal_id.stamp = 
        msg->status_list[i].goal_id.stamp.toSec();         
      out_msg.status_list[i].goal_id.id = 
        new char[strlen(msg->status_list[i].goal_id.id.c_str()) + 1];
      strcpy(out_msg.status_list[i].goal_id.id, 
             msg->status_list[i].goal_id.id.c_str());

      out_msg.status_list[i].status = msg->status_list[i].status;
      out_msg.status_list[i].text = 
        new char[strlen(msg->status_list[i].text.c_str()) + 1];
      strcpy(out_msg.status_list[i].text, msg->status_list[i].text.c_str());
    }
  
  p->Publish(out_msg);

  for (unsigned int i = 0; i < out_msg.status_list_length; i++)
    {
      if (out_msg.status_list[i].goal_id.id != 0)
        delete[] out_msg.status_list[i].goal_id.id;

      out_msg.status_list[i].goal_id.id = 0;      

      if (out_msg.status_list[i].text != 0)
        delete[] out_msg.status_list[i].text;

      out_msg.status_list[i].text = 0;
    }
  
  if (out_msg.status_list != 0)
    delete[] out_msg.status_list;

  out_msg.status_list = 0;
}

#include "publisher.h"
