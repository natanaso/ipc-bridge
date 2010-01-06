#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/sensor_msgs_LaserScan.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::sensor_msgs::LaserScan> *laser;
ipc_bridge::sensor_msgs::LaserScan scan_msg;

unsigned int ranges_prior_length = 0;
unsigned int intensities_prior_length = 0;
unsigned int frame_id_prior_length = 0;

void callback(const sensor_msgs::LaserScan::ConstPtr &msg)
{ 
  scan_msg.header.seq = msg->header.seq;
  scan_msg.header.stamp = msg->header.stamp.toSec();
  ROS_INFO("%s: frame_id: %s", ros::this_node::getName().c_str(),
           msg->header.frame_id.c_str());

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_length)
    {
      delete[] scan_msg.header.frame_id;
      scan_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      frame_id_prior_length = strlen(msg->header.frame_id.c_str());
    }
  strcpy(scan_msg.header.frame_id, msg->header.frame_id.c_str());
  ROS_INFO("%s: send frame_id: %s", ros::this_node::getName().c_str(),
           scan_msg.header.frame_id);

  scan_msg.angle_min = msg->angle_min;
  scan_msg.angle_max = msg->angle_max;
  scan_msg.angle_increment = msg->angle_increment;
  scan_msg.time_increment = msg->time_increment;
  scan_msg.scan_time = msg->scan_time;
  scan_msg.range_min = msg->range_min;
  scan_msg.range_max = msg->range_max;

  scan_msg.ranges_length = msg->ranges.size();
  if (scan_msg.ranges_length > 0)
    {
      if (scan_msg.ranges_length != ranges_prior_length)
        {
          delete[] scan_msg.ranges;
          scan_msg.ranges = new float[scan_msg.ranges_length];
          ranges_prior_length = scan_msg.ranges_length;
        }
      copy(msg->ranges.begin(), msg->ranges.end(), scan_msg.ranges);
    }

  scan_msg.intensities_length = msg->intensities.size();
  if (scan_msg.intensities_length > 0)
    {
      if (scan_msg.intensities_length != intensities_prior_length)
        {
          delete[] scan_msg.intensities;
          scan_msg.intensities = new float[scan_msg.intensities_length];
          intensities_prior_length = scan_msg.intensities_length;
        }
      copy(msg->intensities.begin(), msg->intensities.end(), 
           scan_msg.intensities);
    }
  
  laser->Publish(scan_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sensor_msgs_LaserScan");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("scan"));

  ros::Subscriber sub = n.subscribe("scan", 10, callback);

  laser = new ipc_bridge::Publisher<ipc_bridge::sensor_msgs::LaserScan>(ros::this_node::getName(), 
                                                                message_name);

  if (laser->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  laser->Disconnect();

  if (scan_msg.ranges != 0)
    {
      delete[] scan_msg.ranges;
      scan_msg.ranges = 0;
    }

  if (scan_msg.intensities != 0)
    {
      delete[] scan_msg.intensities;
      scan_msg.intensities = 0;
    }

  if (scan_msg.header.frame_id != 0)
    {
      delete[] scan_msg.header.frame_id;    
      scan_msg.header.frame_id = 0;
    }

  return 0;
}
