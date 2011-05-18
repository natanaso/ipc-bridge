PKG= ipc_std_msgs
MEX_MSGS= Bool
ROS_MSGS= Bool

MEX_FILES := $(foreach msg, $(MEX_MSGS), std_msgs_$(msg))
ROS_FILES := $(foreach msg, $(ROS_MSGS), std_msgs_$(msg)_publisher)
ROS_FILES += $(foreach msg, $(ROS_MSGS), std_msgs_$(msg)_subscriber)

include $(shell rospack find ipc_rosgraph_msgs)/ipc_rosgraph_msgs.mk
include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
