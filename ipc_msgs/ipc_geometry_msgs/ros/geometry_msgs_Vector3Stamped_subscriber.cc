#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Vector3Stamped.h>
#include <ipc_bridge/msgs/geometry_msgs_Vector3Stamped.h>

#define NAMESPACE geometry_msgs
#define NAME Vector3Stamped

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{
  ROS_DEBUG("%s: receiving message", 
            ros::this_node::getName().c_str());

  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);
  if (msg.header.frame_id != 0)
    out_msg.header.frame_id = std::string(msg.header.frame_id);
  else
    out_msg.header.frame_id = std::string("");

  out_msg.vector.x = msg.vector.x;
  out_msg.vector.y = msg.vector.y;
  out_msg.vector.z = msg.vector.z;

  pub.publish(out_msg);
}

#include "subscriber.h"
