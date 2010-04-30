#ifndef __IPC_BRIDGE_MATLAB_ASCTEC_TRIM__
#define __IPC_BRIDGE_MATLAB_ASCTEC_TRIM__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/asctec_Trim.h>

namespace ipc_bridge_matlab
{
  namespace asctec
  {
    namespace Trim
    {
      static mxArray* ProcessMessage(const ipc_bridge::asctec::Trim &msg)
      {
        const char *fields[] = {"thrust", "roll", "pitch", "yaw"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "thrust", mxCreateDoubleScalar(msg.thrust));
        mxSetField(out, 0, "roll", mxCreateDoubleScalar(msg.roll));
        mxSetField(out, 0, "pitch", mxCreateDoubleScalar(msg.pitch));
        mxSetField(out, 0, "yaw", mxCreateDoubleScalar(msg.yaw));
        
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::asctec::Trim &msg)
      {
        mxArray *field;
        
        field = mxGetField(a, 0, "thrust");
        msg.thrust = mxGetScalar(field);

        field = mxGetField(a, 0, "roll");
        msg.roll = mxGetScalar(field);

        field = mxGetField(a, 0, "pitch");
        msg.pitch = mxGetScalar(field);

        field = mxGetField(a, 0, "yaw");
        msg.yaw = mxGetScalar(field);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::asctec::Trim &msg)
      {
        return;
      }
    }
  }
}
#endif
