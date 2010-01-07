#include <ros/ros.h>
#include <vicon/Names.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/vicon_Names.h>

using namespace std;

ipc_bridge::Publisher<ipc_bridge::vicon::Names> *v;
ipc_bridge::vicon::Names vicon_msg;

void callback(const vicon::Names::ConstPtr &msg)
{ 
  vicon_msg.names_length = msg->names.size();

  char *names[vicon_msg.names_length];
  
  for (unsigned int i = 0; i < vicon_msg.names_length; i++)
    {
      names[i] = new char[strlen(msg->names[i].c_str())+1];
      strcpy(names[i], msg->names[i].c_str());
    }
  vicon_msg.names = names;

  v->Publish(vicon_msg);

  for (unsigned int i = 0; i < vicon_msg.names_length; i++)
    delete[] vicon_msg.names[i];
  vicon_msg.names = 0;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vicon_Names_publisher");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("names"));

  ros::Subscriber sub = n.subscribe("names", 10, callback);

  v = new ipc_bridge::Publisher<ipc_bridge::vicon::Names>(ros::this_node::getName(), 
                                                          message_name);

  if (v->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::spin();

  v->Disconnect();

  if (vicon_msg.names != 0)
    {
      for (unsigned int i = 0; i < vicon_msg.names_length; i++)
        {
          delete[] vicon_msg.names[i];
          vicon_msg.names[i] = 0;
        }
      vicon_msg.names = 0;
    }

  return 0;
}
