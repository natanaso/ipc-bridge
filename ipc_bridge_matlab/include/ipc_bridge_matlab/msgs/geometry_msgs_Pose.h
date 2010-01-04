#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Pose.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Point.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_Quaternion.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Pose
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Pose &msg)
      {
        const char *fields[] = {"position", "orientation"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "position", 
                   ipc_bridge_matlab::geometry_msgs::Point::ProcessMessage(msg.position));
        mxSetField(out, 0, "orientation", 
                   ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessMessage(msg.orientation));
                                  
        return out;
      }
      
      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Pose &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "position");
        ipc_bridge_matlab::geometry_msgs::Point::ProcessArray(field, msg.position);

        field = mxGetField(a, 0, "orientation");
        ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessArray(field, msg.orientation);
        
        return SUCCESS;
      }    

      static void Cleanup(ipc_bridge::geometry_msgs::Pose &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Point::Cleanup(msg.position);
        ipc_bridge_matlab::geometry_msgs::Quaternion::Cleanup(msg.orientation);
      }
    }
  }
}
#endif
