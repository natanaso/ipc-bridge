#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <sensor_msgs/Imu.h>
#include <ipc_bridge/msgs/sensor_msgs_Imu.h>

#define NAMESPACE sensor_msgs
#define NAME Imu

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != prior_size)
    {
      if (out_msg.header.frame_id != 0)
        delete[] out_msg.header.frame_id;

      out_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());
      prior_size = strlen(msg->header.frame_id.c_str());
    }

  out_msg.orientation.x = msg->orientation.x;
  out_msg.orientation.y = msg->orientation.y;
  out_msg.orientation.z = msg->orientation.z;
  out_msg.orientation.w = msg->orientation.w;

  out_msg.angular_velocity.x = msg->angular_velocity.x;
  out_msg.angular_velocity.y = msg->angular_velocity.y;
  out_msg.angular_velocity.z = msg->angular_velocity.z;

  out_msg.linear_acceleration.x = msg->linear_acceleration.x;
  out_msg.linear_acceleration.y = msg->linear_acceleration.y;
  out_msg.linear_acceleration.z = msg->linear_acceleration.z;

  std::copy(msg->orientation_covariance.begin(),
            msg->orientation_covariance.end(),
            out_msg.orientation_covariance);
  
  std::copy(msg->angular_velocity_covariance.begin(),
            msg->angular_velocity_covariance.end(),
            out_msg.angular_velocity_covariance);
  
  std::copy(msg->linear_acceleration_covariance.begin(),
            msg->linear_acceleration_covariance.end(),
            out_msg.linear_acceleration_covariance);

  p->Publish(out_msg);
}

#include "publisher.h"
