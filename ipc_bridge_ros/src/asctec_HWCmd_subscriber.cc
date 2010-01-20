#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <asctec/HWCmd.h>
#include <ipc_bridge/msgs/asctec_HWCmd.h>

#define NAMESPACE asctec
#define NAME HWCmd

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.thrust = msg.thrust;
  out_msg.roll = msg.roll;
  out_msg.pitch = msg.pitch;
  out_msg.yaw = msg.yaw;
  for (int i = 0; i < 4; i++)
    out_msg.cmd[i] = msg.cmd[i];

  pub.publish(out_msg);
}

#include "subscriber.h"
