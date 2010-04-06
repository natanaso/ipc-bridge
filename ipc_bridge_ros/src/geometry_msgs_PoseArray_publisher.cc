#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/PoseArray.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseArray.h>

#define NAMESPACE geometry_msgs
#define NAME PoseArray

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

  out_msg.poses_length = msg->poses.size();
  out_msg.poses = new geometry_msgs_Pose[out_msg.poses_length];

  for (unsigned int i = 0; i < out_msg.poses_length; i++)
    {
      out_msg.poses[i].position.x = msg->poses[i].position.x;
      out_msg.poses[i].position.y = msg->poses[i].position.y;
      out_msg.poses[i].position.z = msg->poses[i].position.z;

      out_msg.poses[i].orientation.x = msg->poses[i].orientation.x;
      out_msg.poses[i].orientation.y = msg->poses[i].orientation.y;
      out_msg.poses[i].orientation.z = msg->poses[i].orientation.z;
      out_msg.poses[i].orientation.w = msg->poses[i].orientation.w;
    }
  
  p->Publish(out_msg);
  
  if (out_msg.poses != 0)
    delete [] out_msg.poses;

  out_msg.poses = 0;
}
#include "publisher.h"
