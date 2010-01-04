#include <ros/ros.h>
#include <asctec/DMCmd.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/asctec_DMCmd.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::asctec::DMCmd> *cmd;
ipc_bridge::asctec::DMCmd cmd_msg;

ros::Publisher pub;
asctec::DMCmd out_msg;

void callback(const ipc_bridge::asctec::DMCmd &msg, void* user_ptr)
{ 
  out_msg.u1 = msg.u1;
  out_msg.u2 = msg.u2;
  out_msg.u3 = msg.u3;
  out_msg.u4 = msg.u4;

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "asctec_DMCmd_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("cmd_dm"));

  pub = n.advertise<asctec::DMCmd>("cmd_dm", 100);

  cmd = new ipc_bridge::Subscriber<ipc_bridge::asctec::DMCmd>(ros::this_node::getName(), 
                                                              message_name,
                                                              callback);

  if (cmd->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }

  ros::Rate r(100);

  while (n.ok())
    {
      cmd->Listen(5);
      r.sleep();
    }

  cmd->Disconnect();

  return 0;
}
