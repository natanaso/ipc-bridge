#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <vicon/Values.h>
#include <ipc_bridge/msgs/vicon_Values.h>

#define NAMESPACE vicon
#define NAME Values

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int values_prior_length = 0;
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

  out_msg.values_length = msg->values.size();
  if (out_msg.values_length > 0)
    {
      if (out_msg.values_length != values_prior_length)
        {
          delete[] out_msg.values;
          out_msg.values = new double[out_msg.values_length];
          values_prior_length = out_msg.values_length;
        }
      std::copy(msg->values.begin(), msg->values.end(), out_msg.values);
    }

  p->Publish(out_msg);
}

#include "publisher.h"
