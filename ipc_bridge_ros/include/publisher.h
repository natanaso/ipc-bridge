int main(int argc, char** argv)
{
  ros::init(argc, argv, "NAMESPACE_NAME_publisher");
  ros::NodeHandle n("~");

  std::string message_name;
  n.param("message", message_name, std::string("message"));

  std::string server_name;
  n.param("server", server_name, std::string("localhost"));

  ros::Subscriber sub = n.subscribe("topic", 10, callback);

  p = new ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME>(ros::this_node::getName(), 
                                                             message_name,
                                                             server_name);

  if (p->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s:%s", 
                ros::this_node::getName().c_str(), 
                server_name.c_str(),
                message_name.c_str());
      return -1;
    }
  else
    {
      ROS_DEBUG("%s: connected to message %s:%s", 
                ros::this_node::getName().c_str(), 
                server_name.c_str(),
                message_name.c_str());
    }

  ros::spin();

  p->Disconnect();

  return 0;
}
