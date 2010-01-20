#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <tf/transform_listener.h>
#include <ipc_bridge/msgs/tf_tfMessage.h>

#define NAMESPACE tf
#define NAME tfMessage

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{ 
  out_msg.transforms.resize(msg.transforms_length);

  for (unsigned int i = 0; i < msg.transforms_length; i++)
    {
      out_msg.transforms[i].header.seq = 
        msg.transforms[i].header.seq;
      out_msg.transforms[i].header.stamp = 
        ros::Time(msg.transforms[i].header.stamp);
      out_msg.transforms[i].header.frame_id = 
        std::string(msg.transforms[i].header.frame_id);
      out_msg.transforms[i].child_frame_id = 
        std::string(msg.transforms[i].child_frame_id);
      out_msg.transforms[i].transform.translation.x = 
        msg.transforms[i].transform.translation.x;
      out_msg.transforms[i].transform.translation.y = 
        msg.transforms[i].transform.translation.y;
      out_msg.transforms[i].transform.translation.z = 
        msg.transforms[i].transform.translation.z;
      out_msg.transforms[i].transform.rotation.x = 
        msg.transforms[i].transform.rotation.x;
      out_msg.transforms[i].transform.rotation.y = 
        msg.transforms[i].transform.rotation.y;
      out_msg.transforms[i].transform.rotation.z = 
        msg.transforms[i].transform.rotation.z;
      out_msg.transforms[i].transform.rotation.w = 
        msg.transforms[i].transform.rotation.w;
    }

  pub.publish(out_msg);
}

#include "subscriber.h"
