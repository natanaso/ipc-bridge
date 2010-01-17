#include <ros/ros.h>
#include <tf/transform_listener.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/tf_tfMessage.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::tf::tfMessage> *t;
ipc_bridge::tf::tfMessage tf_msg;

vector<unsigned int> frame_id_prior_length;
unsigned int prior_transforms_length = 0;

void callback(const tf::tfMessageConstPtr &msg)
{  
  tf_msg.transforms_length = msg->transforms.size();
  tf_msg.transforms = new geometry_msgs_TransformStamped[tf_msg.transforms_length];

  for (unsigned int i = 0; i < tf_msg.transforms_length; i++)
    {
      tf_msg.transforms[i].header.seq = msg->transforms[0].header.seq;
      tf_msg.transforms[i].header.stamp = msg->transforms[0].header.stamp.toSec();
      tf_msg.transforms[i].header.frame_id = 
        new char[strlen(msg->transforms[i].header.frame_id.c_str()) + 1];
      strcpy(tf_msg.transforms[i].header.frame_id, 
             msg->transforms[i].header.frame_id.c_str());
      tf_msg.transforms[i].child_frame_id = 
        new char[strlen(msg->transforms[i].child_frame_id.c_str()) + 1];
      strcpy(tf_msg.transforms[i].child_frame_id, 
             msg->transforms[i].child_frame_id.c_str());
      tf_msg.transforms[i].transform.translation.x = 
        msg->transforms[i].transform.translation.x;
      tf_msg.transforms[i].transform.translation.y = 
        msg->transforms[i].transform.translation.y;
      tf_msg.transforms[i].transform.translation.z = 
        msg->transforms[i].transform.translation.z;
      tf_msg.transforms[i].transform.rotation.x = 
        msg->transforms[i].transform.rotation.x;
      tf_msg.transforms[i].transform.rotation.y = 
        msg->transforms[i].transform.rotation.y;
      tf_msg.transforms[i].transform.rotation.z = 
        msg->transforms[i].transform.rotation.z;
      tf_msg.transforms[i].transform.rotation.w = 
        msg->transforms[i].transform.rotation.w;
    }

  t->Publish(tf_msg);

  for (unsigned int i = 0; i < tf_msg.transforms_length; i++)
    {
      delete[] tf_msg.transforms[i].header.frame_id;
      tf_msg.transforms[i].header.frame_id = 0;
      delete[] tf_msg.transforms[i].child_frame_id;
      tf_msg.transforms[i].child_frame_id = 0;
    }

  delete[] tf_msg.transforms;
  tf_msg.transforms = 0;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf_tfMessage_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("tf"));

  string server_name;
  n.param("server", server_name, string("localhost"));

  ros::Subscriber sub = n.subscribe("tf", 10, callback);

  t = new ipc_bridge::Publisher<ipc_bridge::tf::tfMessage>(ros::this_node::getName(), 
                                                           message_name,
                                                           server_name);

  if (t->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s:%s", 
                ros::this_node::getName().c_str(), 
                server_name.c_str(),
                message_name.c_str());
      return -1;
    }

  tf_msg.transforms = 0;

  ros::spin();

  t->Disconnect();

  return 0;
}
