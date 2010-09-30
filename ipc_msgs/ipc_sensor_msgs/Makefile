PKG= ipc_sensor_msgs
MEX_MSGS= ChannelFloat32 LaserScan Image PointCloud Imu
ROS_MSGS= 

MEX_FILES := $(foreach msg, $(MEX_MSGS), sensor_msgs_$(msg))
ROS_FILES := $(foreach msg, $(ROS_MSGS), sensor_msgs_$(msg)_publisher)
ROS_FILES += $(foreach msg, $(ROS_MSGS), sensor_msgs_$(msg)_subscriber)

include $(shell rospack find ipc_roslib)/ipc_roslib.mk
include $(shell rospack find ipc_geometry_msgs)/ipc_geometry_msgs.mk
include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk


