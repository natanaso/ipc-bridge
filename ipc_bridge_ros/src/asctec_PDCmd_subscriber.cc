#include <ros/ros.h>
#include <asctec/PDCmd.h>

#include <ipc_bridge/ipc_bridge.h>
#include <ipc_bridge/msgs/asctec_PDCmd.h>

using namespace std;

ipc_bridge::Subscriber<ipc_bridge::asctec::PDCmd> *cmd;
ipc_bridge::asctec::PDCmd cmd_msg;

ros::Publisher pub;
asctec::PDCmd out_msg;

void callback(const ipc_bridge::asctec::PDCmd &msg)
{ 
  out_msg.thrust = msg.thrust;
  out_msg.roll = msg.roll;
  out_msg.pitch = msg.pitch;
  out_msg.yaw_delta = msg.yaw_delta;

  out_msg.kp_roll = msg.kp_roll;
  out_msg.kd_roll = msg.kd_roll;
  out_msg.kp_pitch = msg.kp_pitch;
  out_msg.kd_pitch = msg.kd_pitch;
  out_msg.kd_yaw = msg.kd_yaw;

  pub.publish(out_msg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "asctec_PDCmd_subscriber");
  ros::NodeHandle n("~");

  string message_name;
  n.param("message", message_name, string("cmd_pd"));

  pub = n.advertise<asctec::PDCmd>("cmd_pd", 100);

  cmd = new ipc_bridge::Subscriber<ipc_bridge::asctec::PDCmd>(ros::this_node::getName(), 
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
