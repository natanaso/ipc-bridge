#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovariance.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseWithCovariance.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::geometry_msgs::PoseWithCovariance> *t;
ipc_bridge::geometry_msgs::PoseWithCovariance out_msg;

void callback(const geometry_msgs::PoseWithCovariance::ConstPtr &msg)
{  
  out_msg.pose.position.x = msg->pose.position.x;
  out_msg.pose.position.y = msg->pose.position.y;
  out_msg.pose.position.z = msg->pose.position.z;

  out_msg.pose.orientation.x = msg->pose.orientation.x;
  out_msg.pose.orientation.y = msg->pose.orientation.y;
  out_msg.pose.orientation.z = msg->pose.orientation.z;
  out_msg.pose.orientation.w = msg->pose.orientation.w;

  for (int i = 0; i < 36; i++)
    out_msg.covariance[i] = msg->covariance[i];

  t->Publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "geometry_msgs_PoseWithCovariance_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("posewithcovariance"));

  string server_name;
  n.param("server", server_name, string("localhost"));

  ros::Subscriber sub = n.subscribe("posewithcovariance", 10, callback);

  t = new ipc_bridge::Publisher<ipc_bridge::geometry_msgs::PoseWithCovariance>(ros::this_node::getName(), 
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

  ros::spin();

  t->Disconnect();

  return 0;
}
