#include <ros/ros.h>
#include <geometry_msgs/Pose.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/geometry_msgs_Pose.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::geometry_msgs::Pose> *g;

ros::Publisher pub;
geometry_msgs::Pose out_msg;

void callback(const ipc_bridge::geometry_msgs::Pose &msg)
{ 
  out_msg.position.x = msg.position.x;
  out_msg.position.y = msg.position.y;
  out_msg.position.z = msg.position.z;

  out_msg.orientation.x = msg.orientation.x;
  out_msg.orientation.y = msg.orientation.y;
  out_msg.orientation.z = msg.orientation.z;
  out_msg.orientation.w = msg.orientation.w;

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "geometry_msgs_Pose_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("pose"));

  string server_name;
  n.param("server", server_name, string("localhost"));

  pub = n.advertise<geometry_msgs::Pose>("pose", 100);
  
  g = new ipc_bridge::Subscriber<ipc_bridge::geometry_msgs::Pose>(ros::this_node::getName(), 
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
