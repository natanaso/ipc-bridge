PKG= ipc_rosgraph_msgs
MSGS= Header

MEX_FILES := $(foreach msg, $(MSGS), rosgraph_msgs_$(msg))
ROS_FILES :=

include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
