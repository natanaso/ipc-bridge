#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/Vector3.h>
#include <ipc_bridge/msgs/geometry_msgs_Vector3.h>

#define NAMESPACE geometry_msgs
#define NAME Vector3

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{
  out_msg.x = msg.x;
  out_msg.y = msg.y;
  out_msg.z = msg.z;

  pub.publish(out_msg);
}

#include "subscriber.h"
