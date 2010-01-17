#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovariance.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseWithCovariance.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::geometry_msgs::PoseWithCovariance> *g;

ros::Publisher pub;
geometry_msgs::PoseWithCovariance out_msg;

void callback(const ipc_bridge::geometry_msgs::PoseWithCovariance &msg)
{ 
  out_msg.pose.position.x = msg.pose.position.x;
  out_msg.pose.position.y = msg.pose.position.y;
  out_msg.pose.position.z = msg.pose.position.z;

  out_msg.pose.orientation.x = msg.pose.orientation.x;
  out_msg.pose.orientation.y = msg.pose.orientation.y;
  out_msg.pose.orientation.z = msg.pose.orientation.z;
  out_msg.pose.orientation.w = msg.pose.orientation.w;

  for (int i = 0; i < 36; i++)
    out_msg.covariance[i] = msg.covariance[i];

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "geometry_msgs_PoseWithCovariance_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("posewithcovariance"));

  string server_name;
  n.param("server", server_name, string("localhost"));

  pub = n.advertise<geometry_msgs::Pose>("posewithcovariance", 100);
  
  g = new ipc_bridge::Subscriber<ipc_bridge::geometry_msgs::PoseWithCovariance>(ros::this_node::getName(), 
                                                                                message_name,
                                                                                server_name,
                                                                                callback);

  if (g->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::Rate r(1000);

  while (n.ok())
    {
      g->Listen(0);
      r.sleep();
    }

  g->Disconnect();

  return 0;
}
