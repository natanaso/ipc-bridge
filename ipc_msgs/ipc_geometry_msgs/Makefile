PKG= ipc_geometry_msgs
MEX_MSGS= Point Point32 PointStamped Pose PoseArray PoseStamped PoseWithCovariance PoseWithCovarianceStamped Quaternion Transform Twist TwistStamped TwistWithCovariance Vector3 Vector3Stamped Wrench
ROS_MSGS= PoseArray PoseStamped PoseWithCovariance Pose Quaternion Twist Vector3 Vector3Stamped

MEX_FILES := $(foreach msg, $(MEX_MSGS), geometry_msgs_$(msg))
ROS_FILES := $(foreach msg, $(ROS_MSGS), geometry_msgs_$(msg)_publisher)
ROS_FILES += $(foreach msg, $(ROS_MSGS), geometry_msgs_$(msg)_subscriber)

include $(shell rospack find ipc_rosgraph_msgs)/ipc_rosgraph_msgs.mk
include $(shell rospack find ipc_bridge_local)/ipc_bridge_local.mk
