cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

rosbuild_add_executable(sensor_msgs_Imu_publisher src/sensor_msgs_Imu_publisher.cc)
rosbuild_add_executable(sensor_msgs_LaserScan_publisher src/sensor_msgs_LaserScan_publisher.cc)
rosbuild_add_executable(asctec_HWCmd_subscriber src/asctec_HWCmd_subscriber.cc)
rosbuild_add_executable(asctec_PDCmd_subscriber src/asctec_PDCmd_subscriber.cc)
rosbuild_add_executable(asctec_DMCmd_subscriber src/asctec_DMCmd_subscriber.cc)
rosbuild_add_executable(vicon_Names_publisher src/vicon_Names_publisher.cc)
rosbuild_add_executable(vicon_Values_publisher src/vicon_Values_publisher.cc)
rosbuild_add_executable(vicon_Subject_subscriber src/vicon_Subject_subscriber.cc)
rosbuild_add_executable(geometry_msgs_Pose_subscriber 
                                        src/geometry_msgs_Pose_subscriber.cc)
rosbuild_add_executable(geometry_msgs_Pose_publisher 
                                        src/geometry_msgs_Pose_publisher.cc)
rosbuild_add_executable(geometry_msgs_PoseArray_publisher 
                                        src/geometry_msgs_PoseArray_publisher.cc)

rosbuild_add_executable(sensor_msgs_Image_publisher src/sensor_msgs_Image_publisher.cc)
rosbuild_add_executable(tf_tfMessage_subscriber src/tf_tfMessage_subscriber.cc)
rosbuild_add_executable(tf_tfMessage_publisher src/tf_tfMessage_publisher.cc)

rosbuild_add_executable(geometry_msgs_PoseWithCovariance_subscriber
                                        src/geometry_msgs_PoseWithCovariance_subscriber.cc)     
rosbuild_add_executable(geometry_msgs_PoseWithCovariance_publisher 
                                        src/geometry_msgs_PoseWithCovariance_publisher.cc)

rosbuild_add_executable(geometry_msgs_PoseStamped_subscriber
                                        src/geometry_msgs_PoseStamped_subscriber.cc)     
rosbuild_add_executable(geometry_msgs_PoseStamped_publisher 
                                        src/geometry_msgs_PoseStamped_publisher.cc)

rosbuild_add_executable(nav_msgs_Odometry_publisher src/nav_msgs_Odometry_publisher.cc)

rosbuild_add_executable(move_base_msgs_MoveBaseActionGoal_publisher
        src/move_base_msgs_MoveBaseActionGoal_publisher.cc)
rosbuild_add_executable(move_base_msgs_MoveBaseActionGoal_subscriber
        src/move_base_msgs_MoveBaseActionGoal_subscriber.cc)

rosbuild_add_executable(move_base_msgs_MoveBaseActionFeedback_publisher
        src/move_base_msgs_MoveBaseActionFeedback_publisher.cc)
rosbuild_add_executable(move_base_msgs_MoveBaseActionFeedback_subscriber
        src/move_base_msgs_MoveBaseActionFeedback_subscriber.cc)

rosbuild_add_executable(move_base_msgs_MoveBaseActionResult_publisher
        src/move_base_msgs_MoveBaseActionResult_publisher.cc)
rosbuild_add_executable(move_base_msgs_MoveBaseActionResult_subscriber
        src/move_base_msgs_MoveBaseActionResult_subscriber.cc)

rosbuild_add_executable(actionlib_msgs_GoalID_publisher
        src/actionlib_msgs_GoalID_publisher.cc)
rosbuild_add_executable(actionlib_msgs_GoalID_subscriber
        src/actionlib_msgs_GoalID_subscriber.cc)

rosbuild_add_executable(actionlib_msgs_GoalStatusArray_publisher
        src/actionlib_msgs_GoalStatusArray_publisher.cc)
rosbuild_add_executable(actionlib_msgs_GoalStatusArray_subscriber
        src/actionlib_msgs_GoalStatusArray_subscriber.cc)

rosbuild_add_executable(sensor_msgs_PointCloud_subscriber
        src/sensor_msgs_PointCloud_subscriber.cc)
