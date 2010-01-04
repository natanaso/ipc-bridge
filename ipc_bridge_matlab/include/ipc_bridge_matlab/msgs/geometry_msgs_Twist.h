#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Twist.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Vector3.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Twist
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Twist &msg)
      {
        const char *fields[] = {"linear", "angular"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "linear", 
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.linear));
        mxSetField(out, 0, "angular", 
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.angular));
        
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::Twist &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "linear");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.linear);

        field = mxGetField(a, 0, "angular");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.angular);
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Twist &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.linear);
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.angular);
        return;
      }
    }
  }
}
#endif
