#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <std_msgs/Bool.h>
#include <ipc_bridge/msgs/std_msgs_Bool.h>

#define NAMESPACE std_msgs
#define NAME Bool

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.data = msg.data > 0 ? true : false;

  pub.publish(out_msg);
}

#include "subscriber.h"
