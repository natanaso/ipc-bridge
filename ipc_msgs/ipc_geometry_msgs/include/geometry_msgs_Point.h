#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Point.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Point
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Point &msg)
      {
        const char *fields[] = {"x", "y", "z"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "x", mxCreateDoubleScalar(msg.x));
        mxSetField(out, 0, "y", mxCreateDoubleScalar(msg.y));
        mxSetField(out, 0, "z", mxCreateDoubleScalar(msg.z));
                                  
        return out;
      }
      
      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Point &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "x");
        msg.x = mxGetScalar(field);

        field = mxGetField(a, 0, "y");
        msg.y = mxGetScalar(field);

        field = mxGetField(a, 0, "z");
        msg.z = mxGetScalar(field);
        
        return SUCCESS;
      }    

      static void Cleanup(ipc_bridge::geometry_msgs::Point &msg)
      {
        return;
      }
    }
  }
}
#endif
