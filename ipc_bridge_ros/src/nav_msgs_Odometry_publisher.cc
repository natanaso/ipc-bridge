#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/nav_msgs_Odometry.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::nav_msgs::Odometry> *odom;
ipc_bridge::nav_msgs::Odometry odom_msg;

unsigned int frame_id_prior_size = 0;
unsigned int child_frame_id_prior_size = 0;

void callback(const nav_msgs::Odometry::ConstPtr &msg)
{ 
  odom_msg.header.seq = msg->header.seq;
  odom_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_size)
    {
      if (odom_msg.header.frame_id != 0)
        delete[] odom_msg.header.frame_id;

      odom_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      strcpy(odom_msg.header.frame_id, msg->header.frame_id.c_str());
      frame_id_prior_size = strlen(msg->header.frame_id.c_str());
    }

  if (strlen(msg->child_frame_id.c_str()) != child_frame_id_prior_size)
    {
      if (odom_msg.child_frame_id != 0)
        delete[] odom_msg.child_frame_id;

      odom_msg.child_frame_id = 
        new char[strlen(msg->child_frame_id.c_str()) + 1];
      strcpy(odom_msg.child_frame_id, msg->child_frame_id.c_str());
      child_frame_id_prior_size = strlen(msg->child_frame_id.c_str());
    }

  odom_msg.pose.pose.position.x = msg->pose.pose.position.x;
  odom_msg.pose.pose.position.y = msg->pose.pose.position.y;
  odom_msg.pose.pose.position.z = msg->pose.pose.position.z;

  odom_msg.pose.pose.orientation.x = msg->pose.pose.orientation.x;
  odom_msg.pose.pose.orientation.y = msg->pose.pose.orientation.y;
  odom_msg.pose.pose.orientation.z = msg->pose.pose.orientation.z;
  odom_msg.pose.pose.orientation.w = msg->pose.pose.orientation.w;

  copy(msg->pose.covariance.begin(),
       msg->pose.covariance.end(),
       odom_msg.pose.covariance);

  odom_msg.twist.twist.linear.x = msg->twist.twist.linear.x;
  odom_msg.twist.twist.linear.y = msg->twist.twist.linear.y;
  odom_msg.twist.twist.linear.z = msg->twist.twist.linear.z;

  odom_msg.twist.twist.angular.x = msg->twist.twist.angular.x;
  odom_msg.twist.twist.angular.y = msg->twist.twist.angular.y;
  odom_msg.twist.twist.angular.z = msg->twist.twist.angular.z;

  copy(msg->twist.covariance.begin(),
       msg->twist.covariance.end(),
       odom_msg.twist.covariance);
  
  odom->Publish(odom_msg);   
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "nav_msgs_Odometry_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("odom"));

  ros::Subscriber sub = n.subscribe("odom", 10, callback);

  odom = 
    new ipc_bridge::Publisher<ipc_bridge::nav_msgs::Odometry>(ros::this_node::getName(), 
                                                              message_name);

  if (odom->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  odom->Disconnect();

  return 0;
}
