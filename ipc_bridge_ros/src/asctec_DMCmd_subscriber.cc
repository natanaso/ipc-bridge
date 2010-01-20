#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <asctec/DMCmd.h>
#include <ipc_bridge/msgs/asctec_DMCmd.h>

#define NAMESPACE asctec
#define NAME DMCmd

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.u1 = msg.u1;
  out_msg.u2 = msg.u2;
  out_msg.u3 = msg.u3;
  out_msg.u4 = msg.u4;

  pub.publish(out_msg);
}

#include "subscriber.h"
