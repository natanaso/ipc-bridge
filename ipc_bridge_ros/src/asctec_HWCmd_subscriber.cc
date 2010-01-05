#include <ros/ros.h>
#include <asctec/HWCmd.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/asctec_HWCmd.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::asctec::HWCmd> *cmd;
ipc_bridge::asctec::HWCmd cmd_msg;

ros::Publisher pub;
asctec::HWCmd out_msg;

void callback(const ipc_bridge::asctec::HWCmd &msg, void* user_ptr)
{ 
  out_msg.thrust = msg.thrust;
  out_msg.roll = msg.roll;
  out_msg.pitch = msg.pitch;
  out_msg.yaw = msg.yaw;
  for (int i = 0; i < 4; i++)
    out_msg.cmd[i] = msg.cmd[i];

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "asctec_HWCmd_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("cmd_hw"));

  pub = n.advertise<asctec::HWCmd>("cmd_hw", 100);

  cmd = new ipc_bridge::Subscriber<ipc_bridge::asctec::HWCmd>(ros::this_node::getName(), 
                                                              message_name,
                                                              callback);

  if (cmd->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::Rate r(1000);

  while (n.ok())
    {
      cmd->Listen(0);
      r.sleep();
    }

  cmd->Disconnect();

  return 0;
}
