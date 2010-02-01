#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

int main(int argc, char** argv)
{
  ros::init(argc, argv, STR(NAMESPACE)"_"STR(NAME)"_subscriber");
  ros::NodeHandle n("~");

  std::string message_name;
  n.param("message", message_name, std::string("message"));

  pub = n.advertise<NAMESPACE::NAME>("topic", 100);

  ipc_bridge::Subscriber<ipc_bridge::NAMESPACE::NAME> s(ros::this_node::getName(), 
                                                        message_name,
                                                        callback);
  if (s.Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }
  else
    {
      ROS_DEBUG("%s: connected to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
    }

  while (n.ok())
    s.Listen(2);

  s.Disconnect();

  return 0;
}
