#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Vector3Stamped.h>
#include <ipc_bridge/msgs/geometry_msgs_Vector3Stamped.h>

#define NAMESPACE geometry_msgs
#define NAME Vector3Stamped

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  ROS_DEBUG("%s: publishing message", 
            ros::this_node::getName().c_str());

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

  out_msg.vector.x = msg->vector.x;
  out_msg.vector.y = msg->vector.y;
  out_msg.vector.z = msg->vector.z;

  p->Publish(out_msg);
}

#include "publisher.h"
