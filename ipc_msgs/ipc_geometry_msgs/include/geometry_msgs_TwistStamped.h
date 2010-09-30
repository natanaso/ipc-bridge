#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST_STAMPED__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST_STAMPED__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_TwistStamped.h>

#include <roslib_Header.h>
#include <geometry_msgs_Twist.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace TwistStamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::TwistStamped &msg)
      {
        const char *fields[] = {"header", "twist"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "twist", 
                   ipc_bridge_matlab::geometry_msgs::Twist::ProcessMessage(msg.twist));
        
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::TwistStamped &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "twist");
        ipc_bridge_matlab::geometry_msgs::Twist::ProcessArray(field, msg.twist);
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::TwistStamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::Twist::Cleanup(msg.twist);
        return;
      }
    }
  }
}
#endif
