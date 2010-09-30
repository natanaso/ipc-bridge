#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_QUATERNION__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_QUATERNION__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Quaternion.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Quaternion
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Quaternion &msg)
      {
        const char *fields[] = {"x", "y", "z", "w"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "x", mxCreateDoubleScalar(msg.x));
        mxSetField(out, 0, "y", mxCreateDoubleScalar(msg.y));
        mxSetField(out, 0, "z", mxCreateDoubleScalar(msg.z));
        mxSetField(out, 0, "w", mxCreateDoubleScalar(msg.w));
        
        return out;
      }
      
      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Quaternion &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "x");
        msg.x = mxGetScalar(field);

        field = mxGetField(a, 0, "y");
        msg.y = mxGetScalar(field);

        field = mxGetField(a, 0, "z");
        msg.z = mxGetScalar(field);

        field = mxGetField(a, 0, "w");
        msg.w = mxGetScalar(field);
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Quaternion &msg)
      {
        return;
      }
    }
  }
}
#endif
