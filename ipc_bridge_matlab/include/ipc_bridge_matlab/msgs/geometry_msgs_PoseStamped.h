#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE_STAMPED__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE_STAMPED__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseStamped.h>

#include <ipc_bridge_matlab/msgs/roslib_Header.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_Pose.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace PoseStamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::PoseStamped &msg)
      {
        const char *fields[] = {"header", "pose"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "pose", 
                   ipc_bridge_matlab::geometry_msgs::Pose::ProcessMessage(msg.pose));
                                  
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::PoseStamped &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "pose");
        ipc_bridge_matlab::geometry_msgs::Pose::ProcessArray(field, msg.pose);
        
        return SUCCESS;
      }    

      static void Cleanup(ipc_bridge::geometry_msgs::PoseStamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::Pose::Cleanup(msg.pose);
      }
    }
  }
}
#endif
