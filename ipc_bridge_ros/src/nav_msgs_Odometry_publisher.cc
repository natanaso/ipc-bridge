#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <nav_msgs/Odometry.h>
#include <ipc_bridge/msgs/nav_msgs_Odometry.h>

#define NAMESPACE nav_msgs
#define NAME Odometry

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;
unsigned int child_frame_id_prior_size = 0;

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

  if (strlen(msg->child_frame_id.c_str()) != child_frame_id_prior_size)
    {
      if (out_msg.child_frame_id != 0)
        delete[] out_msg.child_frame_id;

      out_msg.child_frame_id = 
        new char[strlen(msg->child_frame_id.c_str()) + 1];
      strcpy(out_msg.child_frame_id, msg->child_frame_id.c_str());
      child_frame_id_prior_size = strlen(msg->child_frame_id.c_str());
    }

  out_msg.pose.pose.position.x = msg->pose.pose.position.x;
  out_msg.pose.pose.position.y = msg->pose.pose.position.y;
  out_msg.pose.pose.position.z = msg->pose.pose.position.z;

  out_msg.pose.pose.orientation.x = msg->pose.pose.orientation.x;
  out_msg.pose.pose.orientation.y = msg->pose.pose.orientation.y;
  out_msg.pose.pose.orientation.z = msg->pose.pose.orientation.z;
  out_msg.pose.pose.orientation.w = msg->pose.pose.orientation.w;

  std::copy(msg->pose.covariance.begin(),
            msg->pose.covariance.end(),
            out_msg.pose.covariance);

  out_msg.twist.twist.linear.x = msg->twist.twist.linear.x;
  out_msg.twist.twist.linear.y = msg->twist.twist.linear.y;
  out_msg.twist.twist.linear.z = msg->twist.twist.linear.z;

  out_msg.twist.twist.angular.x = msg->twist.twist.angular.x;
  out_msg.twist.twist.angular.y = msg->twist.twist.angular.y;
  out_msg.twist.twist.angular.z = msg->twist.twist.angular.z;

  std::copy(msg->twist.covariance.begin(),
            msg->twist.covariance.end(),
            out_msg.twist.covariance);
  
  p->Publish(out_msg);   
}

#include "publisher.h"
