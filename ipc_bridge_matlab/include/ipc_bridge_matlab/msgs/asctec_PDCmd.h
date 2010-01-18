#ifndef __IPC_BRIDGE_MATLAB_ASCTEC_PDCMD__
#define __IPC_BRIDGE_MATLAB_ASCTEC_PDCMD__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/asctec_PDCmd.h>

namespace ipc_bridge_matlab
{
  namespace asctec
  {
    namespace PDCmd
    {
      static mxArray* ProcessMessage(const ipc_bridge::asctec::PDCmd &msg)
      {
        const char *fields[] = {"thrust", "roll", "pitch", "yaw_delta",
                                "kp_roll", "kd_roll", 
                                "kp_pitch", "kd_pitch", "kd_yaw"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "thrust", mxCreateDoubleScalar(msg.thrust));
        mxSetField(out, 0, "roll", mxCreateDoubleScalar(msg.roll));
        mxSetField(out, 0, "pitch", mxCreateDoubleScalar(msg.pitch));
        mxSetField(out, 0, "yaw_delta", mxCreateDoubleScalar(msg.yaw_delta));
        mxSetField(out, 0, "kp_roll", mxCreateDoubleScalar(msg.kp_roll));
        mxSetField(out, 0, "kd_roll", mxCreateDoubleScalar(msg.kd_roll));
        mxSetField(out, 0, "kp_pitch", mxCreateDoubleScalar(msg.kp_pitch));
        mxSetField(out, 0, "kd_pitch", mxCreateDoubleScalar(msg.kd_pitch));
        mxSetField(out, 0, "kd_yaw", mxCreateDoubleScalar(msg.kd_yaw));
        
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::asctec::PDCmd &msg)
      {
        mxArray *field;
        
        field = mxGetField(a, 0, "thrust");
        msg.thrust = mxGetScalar(field);

        field = mxGetField(a, 0, "roll");
        msg.roll = mxGetScalar(field);

        field = mxGetField(a, 0, "pitch");
        msg.pitch = mxGetScalar(field);

        field = mxGetField(a, 0, "yaw_delta");
        msg.yaw_delta = mxGetScalar(field);

        field = mxGetField(a, 0, "kp_roll");
        msg.kp_roll = mxGetScalar(field);

        field = mxGetField(a, 0, "kd_roll");
        msg.kd_roll = mxGetScalar(field);

        field = mxGetField(a, 0, "kp_pitch");
        msg.kp_pitch = mxGetScalar(field);

        field = mxGetField(a, 0, "kd_pitch");
        msg.kd_pitch = mxGetScalar(field);

        field = mxGetField(a, 0, "kd_yaw");
        msg.kd_yaw = mxGetScalar(field);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::asctec::PDCmd &msg)
      {
        return;
      }
    }
  }
}
#endif
