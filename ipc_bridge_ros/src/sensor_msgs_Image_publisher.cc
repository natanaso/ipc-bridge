#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/sensor_msgs_Image.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::sensor_msgs::Image> *image;
ipc_bridge::sensor_msgs::Image image_msg;

unsigned int data_prior_length = 0;
unsigned int frame_id_prior_length = 0;
unsigned int encoding_prior_length = 0;

void callback(const sensor_msgs::Image::ConstPtr &msg)
{ 
  image_msg.header.seq = msg->header.seq;
  image_msg.header.stamp = msg->header.stamp.toSec();
  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_length)
    {
      delete[] image_msg.header.frame_id;
      image_msg.header.frame_id = 
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      frame_id_prior_length = strlen(msg->header.frame_id.c_str());
    }
  strcpy(image_msg.header.frame_id, msg->header.frame_id.c_str());

  image_msg.height = msg->height;
  image_msg.width = msg->width;
  if (strlen(msg->encoding.c_str()) != encoding_prior_length)
    {
      delete[] image_msg.encoding;
      image_msg.encoding = 
        new char[strlen(msg->encoding.c_str()) + 1];
      encoding_prior_length = strlen(msg->encoding.c_str());
    }
  strcpy(image_msg.encoding, msg->encoding.c_str());
  image_msg.is_bigendian = msg->is_bigendian;
  image_msg.step = msg->step;
  image_msg.data_length = msg->data.size();
  if (image_msg.data_length > 0)
    {
      if (image_msg.data_length != data_prior_length)
        {
          delete[] image_msg.data;
          image_msg.data = new unsigned char[image_msg.data_length];
          data_prior_length = image_msg.data_length;
        }
      copy(msg->data.begin(), msg->data.end(), image_msg.data);
    }
  
  image->Publish(image_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sensor_msgs_Image_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("image"));

  ros::Subscriber sub = n.subscribe("image", 10, callback);

  image = new ipc_bridge::Publisher<ipc_bridge::sensor_msgs::Image>(ros::this_node::getName(), 
                                                                message_name);

  if (image->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  image->Disconnect();

  if (image_msg.data != 0)
    {
      delete[] image_msg.data;
      image_msg.data = 0;
    }

  if (image_msg.header.frame_id != 0)
    {
      delete[] image_msg.header.frame_id;    
      image_msg.header.frame_id = 0;
    }

  if (image_msg.encoding != 0)
    {
      delete[] image_msg.encoding;    
      image_msg.encoding = 0;
    }

  return 0;
}
