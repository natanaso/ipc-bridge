#ifndef __IPC_BRIDGE_MATLAB_STD_MSGS_BOOL__
#define __IPC_BRIDGE_MATLAB_STD_MSGS_BOOL__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/std_msgs_Bool.h>

namespace ipc_bridge_matlab
{
  namespace std_msgs
  {
    namespace Bool
    {
      static mxArray* ProcessMessage(const ipc_bridge::std_msgs::Bool &msg)
      {
        const char *fields[] = {"data"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        int d = msg.data > 0 ? 1 : 0;
        
        mxSetField(out, 0, "data", mxCreateDoubleScalar(d));

        return out;
      }
    
      static int ProcessArray(const mxArray *a, ipc_bridge::std_msgs::Bool &msg)
      {
        mxArray *field;
        
        field = mxGetField(a, 0, "data");
        int d = (int)mxGetScalar(field);
        msg.data = d > 0 ? 1 : 0;
     
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::std_msgs::Bool &msg)
      {
      }
    }
  }
}
#endif
