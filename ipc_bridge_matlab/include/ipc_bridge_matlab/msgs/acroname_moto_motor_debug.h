#ifndef __IPC_BRIDGE_MATLAB_ACRONAME_MOTO_MOTOR_DEBUG__
#define __IPC_BRIDGE_MATLAB_ACRONAME_MOTO_MOTOR_DEBUG__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/acroname_moto_motor_debug.h>

namespace ipc_bridge_matlab
{
  namespace acroname_moto
  {
    namespace motor_debug
    {
      static mxArray* ProcessMessage(const ipc_bridge::acroname_moto::motor_debug &msg)
      {
        const char *fields[] = {"sp_enc_left", 
                                "sp_enc_right",
                                "enc_left",
                                "enc_right",
                                "sp_wheel_left",
                                "sp_wheel_right",
                                "wheel_left",
                                "wheel_right",
                                "sp_v",
                                "sp_w",
                                "v",
                                "w"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "sp_enc_left", 
                   mxCreateDoubleScalar(msg.sp_enc_left));
        mxSetField(out, 0, "sp_enc_right", 
                   mxCreateDoubleScalar(msg.sp_enc_right));
        mxSetField(out, 0, "enc_left", 
                   mxCreateDoubleScalar(msg.enc_left));
        mxSetField(out, 0, "enc_right", 
                   mxCreateDoubleScalar(msg.enc_right));
        mxSetField(out, 0, "sp_wheel_left", 
                   mxCreateDoubleScalar(msg.sp_wheel_left));
        mxSetField(out, 0, "sp_wheel_right", 
                   mxCreateDoubleScalar(msg.sp_wheel_right));
        mxSetField(out, 0, "wheel_left", 
                   mxCreateDoubleScalar(msg.wheel_left));
        mxSetField(out, 0, "wheel_right", 
                   mxCreateDoubleScalar(msg.wheel_right));
        mxSetField(out, 0, "sp_v", 
                   mxCreateDoubleScalar(msg.sp_v));
        mxSetField(out, 0, "sp_w", 
                   mxCreateDoubleScalar(msg.sp_w));
        mxSetField(out, 0, "v", 
                   mxCreateDoubleScalar(msg.v));
        mxSetField(out, 0, "w", 
                   mxCreateDoubleScalar(msg.w));
       
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::acroname_moto::motor_debug &msg)
      {
        msg.sp_enc_left = mxGetScalar(mxGetField(a, 0, "sp_enc_left"));
        msg.sp_enc_right = mxGetScalar(mxGetField(a, 0, "sp_enc_right"));
        msg.enc_left = mxGetScalar(mxGetField(a, 0, "enc_left"));
        msg.enc_right = mxGetScalar(mxGetField(a, 0, "enc_right"));
        msg.sp_wheel_left = mxGetScalar(mxGetField(a, 0, "sp_wheel_left"));
        msg.sp_wheel_right = mxGetScalar(mxGetField(a, 0, "sp_wheel_right"));
        msg.wheel_left = mxGetScalar(mxGetField(a, 0, "wheel_left"));
        msg.wheel_right = mxGetScalar(mxGetField(a, 0, "wheel_right"));
        msg.sp_v = mxGetScalar(mxGetField(a, 0, "sp_v"));
        msg.sp_w = mxGetScalar(mxGetField(a, 0, "sp_w"));
        msg.v = mxGetScalar(mxGetField(a, 0, "v"));
        msg.w = mxGetScalar(mxGetField(a, 0, "w"));
     
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::acroname_moto::motor_debug &msg)
      {
        return;
      }
    }
  }
}
#endif
