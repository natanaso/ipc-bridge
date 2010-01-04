#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/sensor_msgs_Imu.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::sensor_msgs::Imu> *imu;
ipc_bridge::sensor_msgs::Imu imu_msg;

void callback(const sensor_msgs::Imu::ConstPtr &msg)
{ 
  imu_msg.header.seq = msg->header.seq;
  imu_msg.header.stamp = msg->header.stamp.toSec();
  imu_msg.header.frame_id = (char*)(msg->header.frame_id.c_str());

  imu_msg.orientation.x = msg->orientation.x;
  imu_msg.orientation.y = msg->orientation.y;
  imu_msg.orientation.z = msg->orientation.z;
  imu_msg.orientation.w = msg->orientation.w;

  imu_msg.angular_velocity.x = msg->angular_velocity.x;
  imu_msg.angular_velocity.y = msg->angular_velocity.y;
  imu_msg.angular_velocity.z = msg->angular_velocity.z;

  imu_msg.linear_acceleration.x = msg->linear_acceleration.x;
  imu_msg.linear_acceleration.y = msg->linear_acceleration.y;
  imu_msg.linear_acceleration.z = msg->linear_acceleration.z;

  copy(msg->orientation_covariance.begin(),
       msg->orientation_covariance.end(),
       imu_msg.orientation_covariance);

  copy(msg->angular_velocity_covariance.begin(),
       msg->angular_velocity_covariance.end(),
       imu_msg.angular_velocity_covariance);

  copy(msg->linear_acceleration_covariance.begin(),
       msg->linear_acceleration_covariance.end(),
       imu_msg.linear_acceleration_covariance);
  
  imu->Publish(imu_msg);   
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sensor_msgs_imu");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("imu"));

  ros::Subscriber sub = n.subscribe("imu", 10, callback);

  imu = new ipc_bridge::Publisher<ipc_bridge::sensor_msgs::Imu>(ros::this_node::getName(), 
                                                                message_name);

  if (imu->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  imu->Disconnect();

  return 0;
}
