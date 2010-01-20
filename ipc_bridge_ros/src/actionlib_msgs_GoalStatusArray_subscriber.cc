#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <actionlib_msgs/GoalStatusArray.h>
#include <ipc_bridge/msgs/actionlib_msgs_GoalStatusArray.h>

#define NAMESPACE actionlib_msgs
#define NAME GoalStatusArray

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
  
  out_msg.status_list.resize(msg.status_list_length);

  for (unsigned int i = 0; i < msg.status_list_length; i++)
    {
      out_msg.status_list[i].goal_id.stamp = 
        ros::Time(msg.status_list[i].goal_id.stamp);
      if (msg.status_list[i].goal_id.id != 0)
        out_msg.status_list[i].goal_id.id = 
          std::string(msg.status_list[i].goal_id.id);
      else
        out_msg.status_list[i].goal_id.id = std::string("");
     
      out_msg.status_list[i].status = msg.status_list[i].status;

      if (msg.status_list[i].text != 0)
        out_msg.status_list[i].text = 
          std::string(msg.status_list[i].text);
      else
        out_msg.status_list[i].text = std::string("");
    }

  pub.publish(out_msg);
}

#include "subscriber.h"
