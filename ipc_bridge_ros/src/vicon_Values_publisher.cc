#include <ros/ros.h>
#include <vicon/Values.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/vicon_Values.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::vicon::Values> *v;
ipc_bridge::vicon::Values vicon_msg;

unsigned int values_prior_length = 0;
unsigned int frame_id_prior_length = 0;

void callback(const vicon::Values::ConstPtr &msg)
{ 
  vicon_msg.header.seq = msg->header.seq;
  vicon_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_length)
    {
      delete[] vicon_msg.header.frame_id;
      vicon_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      frame_id_prior_length = strlen(msg->header.frame_id.c_str());
    }
  strcpy(vicon_msg.header.frame_id, msg->header.frame_id.c_str());

  vicon_msg.values_length = msg->values.size();
  if (vicon_msg.values_length > 0)
    {
      if (vicon_msg.values_length != values_prior_length)
        {
          delete[] vicon_msg.values;
          vicon_msg.values = new double[vicon_msg.values_length];
          values_prior_length = vicon_msg.values_length;
        }
      copy(msg->values.begin(), msg->values.end(), vicon_msg.values);
    }

  v->Publish(vicon_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vicon_Values_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("values"));

  ros::Subscriber sub = n.subscribe("values", 10, callback);

  v = new ipc_bridge::Publisher<ipc_bridge::vicon::Values>(ros::this_node::getName(), 
                                                               message_name);

  if (v->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  v->Disconnect();

  if (vicon_msg.values != 0)
    {
      delete[] vicon_msg.values;
      vicon_msg.values = 0;
    }

  if (vicon_msg.header.frame_id != 0)
    {
      delete[] vicon_msg.header.frame_id;    
      vicon_msg.header.frame_id = 0;
    }

  return 0;
}
