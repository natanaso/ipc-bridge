PKG= ipc_geometry_msgs
MEX_MSGS= Point Point32 PointStamped Pose PoseArray PoseStamped PoseWithCovariance PoseWithCovarianceStamped Quaternion Transform Twist TwistStamped TwistWithCovariance Vector3 Wrench
ROS_MSGS= PoseArray PoseStamped PoseWithCovariance Pose Quaternion Twist

MEX_FILES := $(foreach msg, $(MEX_MSGS), geometry_msgs_$(msg))
ROS_FILES := $(foreach msg, $(ROS_MSGS), geometry_msgs_$(msg)_publisher)
ROS_FILES += $(foreach msg, $(ROS_MSGS), geometry_msgs_$(msg)_subscriber)

include $(shell rospack find ipc_roslib)/ipc_roslib.mk
include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
