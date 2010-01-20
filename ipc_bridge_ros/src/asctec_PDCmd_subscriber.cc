#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <asctec/PDCmd.h>
#include <ipc_bridge/msgs/asctec_PDCmd.h>

#define NAMESPACE asctec
#define NAME PDCmd

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.thrust = msg.thrust;
  out_msg.roll = msg.roll;
  out_msg.pitch = msg.pitch;
  out_msg.yaw_delta = msg.yaw_delta;

  out_msg.kp_roll = msg.kp_roll;
  out_msg.kd_roll = msg.kd_roll;
  out_msg.kp_pitch = msg.kp_pitch;
  out_msg.kd_pitch = msg.kd_pitch;
  out_msg.kd_yaw = msg.kd_yaw;

  pub.publish(out_msg);
}

#include "subscriber.h"
