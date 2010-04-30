#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <asctec/Trim.h>
#include <ipc_bridge/msgs/asctec_Trim.h>

#define NAMESPACE asctec
#define NAME Trim

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.thrust = msg.thrust;
  out_msg.roll = msg.roll;
  out_msg.pitch = msg.pitch;
  out_msg.yaw = msg.yaw;

  pub.publish(out_msg);
}

#include "subscriber.h"
