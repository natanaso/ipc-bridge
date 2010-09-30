PKG= ipc_roslib
MSGS= Header

MEX_FILES := $(foreach msg, $(MSGS), roslib_$(msg))
ROS_FILES :=

include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
