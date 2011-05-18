PKG= ipc_nav_msgs
MEX_MSGS= GridCells MapMetaData OccupancyGrid Odometry Path
ROS_MSGS= Odometry

MEX_FILES := $(foreach msg, $(MEX_MSGS), nav_msgs_$(msg))
ROS_FILES := $(foreach msg, $(ROS_MSGS), nav_msgs_$(msg)_publisher)
ROS_FILES += $(foreach msg, $(ROS_MSGS), nav_msgs_$(msg)_subscriber)

include $(shell rospack find ipc_rosgraph_msgs)/ipc_rosgraph_msgs.mk
include $(shell rospack find ipc_geometry_msgs)/ipc_geometry_msgs.mk
include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
