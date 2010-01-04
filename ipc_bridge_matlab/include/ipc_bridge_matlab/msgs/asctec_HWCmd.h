#ifndef __IPC_BRIDGE_MATLAB_ASCTEC_HWCMD__
#define __IPC_BRIDGE_MATLAB_ASCTEC_HWCMD__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/asctec_HWCmd.h>

namespace ipc_bridge_matlab
{
  namespace asctec
  {
    namespace HWCmd
    {
      static mxArray* ProcessMessage(const ipc_bridge::asctec::HWCmd &msg)
      {
        const char *fields[] = {"thrust", 
                                "roll", 
                                "pitch",
                                "yaw",
                                "cmd"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "thrust", mxCreateDoubleScalar(msg.thrust));
        mxSetField(out, 0, "roll", mxCreateDoubleScalar(msg.roll));
        mxSetField(out, 0, "pitch", mxCreateDoubleScalar(msg.pitch));
        mxSetField(out, 0, "yaw", mxCreateDoubleScalar(msg.yaw));

        mxArray *cmd = mxCreateDoubleMatrix(1, 4, mxREAL);
        std::copy(msg.cmd, msg.cmd + 4, mxGetPr(cmd));
        mxSetField(out, 0, "cmd", cmd);
        
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::asctec::HWCmd &msg)
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

        field = mxGetField(a, 0, "cmd");
        double tmp[4];
        ipc_bridge_matlab::GetDoubleArray(field, 4, tmp);
        for (int i = 0; i < 4; i++)
          msg.cmd[i] = (bool)tmp[i];

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::asctec::HWCmd &msg)
      {
        return;
      }
    }
  }
}
#endif
