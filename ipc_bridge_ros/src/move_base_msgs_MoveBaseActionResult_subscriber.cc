#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <move_base_msgs/MoveBaseActionResult.h>
#include <ipc_bridge/msgs/move_base_msgs_MoveBaseActionResult.h>

#define NAMESPACE move_base_msgs
#define NAME MoveBaseActionResult

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

  pub.publish(out_msg);
}

#include "subscriber.h"
