#include <ros/ros.h>
#include <vicon/Subject.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/vicon_Subject.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::vicon::Subject> *v;

ros::Publisher pub;
vicon::Subject out_msg;

void callback(const ipc_bridge::vicon::Subject &msg)
{ 
  out_msg.name = std::string(msg.name);

  out_msg.pose.position.x = msg.pose.position.x;
  out_msg.pose.position.y = msg.pose.position.y;
  out_msg.pose.position.z = msg.pose.position.z;

  out_msg.pose.orientation.x = msg.pose.orientation.x;
  out_msg.pose.orientation.y = msg.pose.orientation.y;
  out_msg.pose.orientation.z = msg.pose.orientation.z;
  out_msg.pose.orientation.w = msg.pose.orientation.w;

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vicon_Subject_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("subject"));

  pub = n.advertise<vicon::Subject>("subject", 100);
  
  v = new ipc_bridge::Subscriber<ipc_bridge::vicon::Subject>(ros::this_node::getName(), 
                                                             message_name,
                                                             callback);

  if (v->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::Rate r(1000);

  while (n.ok())
    {
      v->Listen(0);
      r.sleep();
    }

  v->Disconnect();

  return 0;
}
