#include <ros/ros.h>
#include <tf/transform_listener.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/tf_tfMessage.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::tf::tfMessage> *t;
ipc_bridge::tf::tfMessage tf_msg;

ros::Publisher pub;
tf::tfMessage out_msg;

void callback(const ipc_bridge::tf::tfMessage &msg)
{ 
  out_msg.transforms.resize(msg.transforms_length);

  for (unsigned int i = 0; i < msg.transforms_length; i++)
    {
      out_msg.transforms[i].header.seq = 
        msg.transforms[i].header.seq;
      out_msg.transforms[i].header.stamp = 
        ros::Time(msg.transforms[i].header.stamp);
      out_msg.transforms[i].header.frame_id = 
        string(msg.transforms[i].header.frame_id);
      out_msg.transforms[i].child_frame_id = 
        string(msg.transforms[i].child_frame_id);
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

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf_tfMessage_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("tf"));

  string server_name;
  n.param("server", server_name, string("localhost"));  

  pub = n.advertise<tf::tfMessage>("/tf", 100);
  
  t = new ipc_bridge::Subscriber<ipc_bridge::tf::tfMessage>(ros::this_node::getName(), 
                                                            message_name,
                                                            server_name,
                                                            callback);

  if (t->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s:%s", 
                ros::this_node::getName().c_str(), 
                server_name.c_str(),
                message_name.c_str());
      return -1;
    }

  ros::Rate r(1000);

  while (n.ok())
    {
      t->Listen(0);
      r.sleep();
    }

  t->Disconnect();

  return 0;
}
