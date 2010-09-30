#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <sensor_msgs/LaserScan.h>
#include <ipc_bridge/msgs/sensor_msgs_LaserScan.h>

#define NAMESPACE sensor_msgs
#define NAME LaserScan

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int ranges_prior_length = 0;
unsigned int intensities_prior_length = 0;
unsigned int frame_id_prior_length = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_length)
    {
      delete[] out_msg.header.frame_id;
      out_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      frame_id_prior_length = strlen(msg->header.frame_id.c_str());
    }
  strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());

  out_msg.angle_min = msg->angle_min;
  out_msg.angle_max = msg->angle_max;
  out_msg.angle_increment = msg->angle_increment;
  out_msg.time_increment = msg->time_increment;
  out_msg.scan_time = msg->scan_time;
  out_msg.range_min = msg->range_min;
  out_msg.range_max = msg->range_max;

  out_msg.ranges_length = msg->ranges.size();
  if (out_msg.ranges_length > 0)
    {
      if (out_msg.ranges_length != ranges_prior_length)
        {
          delete[] out_msg.ranges;
          out_msg.ranges = new float[out_msg.ranges_length];
          ranges_prior_length = out_msg.ranges_length;
        }
      std::copy(msg->ranges.begin(), msg->ranges.end(), out_msg.ranges);
    }

  out_msg.intensities_length = msg->intensities.size();
  if (out_msg.intensities_length > 0)
    {
      if (out_msg.intensities_length != intensities_prior_length)
        {
          delete[] out_msg.intensities;
          out_msg.intensities = new float[out_msg.intensities_length];
          intensities_prior_length = out_msg.intensities_length;
        }
      std::copy(msg->intensities.begin(), msg->intensities.end(), 
                out_msg.intensities);
    }
  
  p->Publish(out_msg);
}

#include "publisher.h"
