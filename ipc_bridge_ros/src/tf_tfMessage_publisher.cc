#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <tf/transform_listener.h>
#include <ipc_bridge/msgs/tf_tfMessage.h>

#define NAMESPACE tf
#define NAME tfMessage

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

std::vector<unsigned int> frame_id_prior_length;
unsigned int prior_transforms_length = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{  
  out_msg.transforms_length = msg->transforms.size();
  out_msg.transforms = new geometry_msgs_TransformStamped[out_msg.transforms_length];

  for (unsigned int i = 0; i < out_msg.transforms_length; i++)
    {
      out_msg.transforms[i].header.seq = msg->transforms[0].header.seq;
      out_msg.transforms[i].header.stamp = msg->transforms[0].header.stamp.toSec();
      out_msg.transforms[i].header.frame_id = 
        new char[strlen(msg->transforms[i].header.frame_id.c_str()) + 1];
      strcpy(out_msg.transforms[i].header.frame_id, 
             msg->transforms[i].header.frame_id.c_str());
      out_msg.transforms[i].child_frame_id = 
        new char[strlen(msg->transforms[i].child_frame_id.c_str()) + 1];
      strcpy(out_msg.transforms[i].child_frame_id, 
             msg->transforms[i].child_frame_id.c_str());
      out_msg.transforms[i].transform.translation.x = 
        msg->transforms[i].transform.translation.x;
      out_msg.transforms[i].transform.translation.y = 
        msg->transforms[i].transform.translation.y;
      out_msg.transforms[i].transform.translation.z = 
        msg->transforms[i].transform.translation.z;
      out_msg.transforms[i].transform.rotation.x = 
        msg->transforms[i].transform.rotation.x;
      out_msg.transforms[i].transform.rotation.y = 
        msg->transforms[i].transform.rotation.y;
      out_msg.transforms[i].transform.rotation.z = 
        msg->transforms[i].transform.rotation.z;
      out_msg.transforms[i].transform.rotation.w = 
        msg->transforms[i].transform.rotation.w;
    }

  p->Publish(out_msg);

  for (unsigned int i = 0; i < out_msg.transforms_length; i++)
    {
      delete[] out_msg.transforms[i].header.frame_id;
      out_msg.transforms[i].header.frame_id = 0;
      delete[] out_msg.transforms[i].child_frame_id;
      out_msg.transforms[i].child_frame_id = 0;
    }

  delete[] out_msg.transforms;
  out_msg.transforms = 0;
}

#include "publisher.h"
