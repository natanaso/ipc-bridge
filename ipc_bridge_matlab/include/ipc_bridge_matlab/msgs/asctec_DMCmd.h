#ifndef __IPC_BRIDGE_MATLAB_ASCTEC_DMCMD__
#define __IPC_BRIDGE_MATLAB_ASCTEC_DMCMD__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/asctec_DMCmd.h>

namespace ipc_bridge_matlab
{
  namespace asctec
  {
    namespace DMCmd
    {
      static mxArray* ProcessMessage(const ipc_bridge::asctec::DMCmd &msg)
      {
        const char *fields[] = {"u1", 
                                "u2", 
                                "u3",
                                "u4"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "u1", mxCreateDoubleScalar(msg.u1));
        mxSetField(out, 0, "u2", mxCreateDoubleScalar(msg.u2));
        mxSetField(out, 0, "u3", mxCreateDoubleScalar(msg.u3));
        mxSetField(out, 0, "u4", mxCreateDoubleScalar(msg.u4));
        
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::asctec::DMCmd &msg)
      {
        mxArray *field;
        
        field = mxGetField(a, 0, "u1");
        msg.u1 = mxGetScalar(field);

        field = mxGetField(a, 0, "u2");
        msg.u2 = mxGetScalar(field);

        field = mxGetField(a, 0, "u3");
        msg.u3 = mxGetScalar(field);

        field = mxGetField(a, 0, "u4");
        msg.u4 = mxGetScalar(field);
     
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::asctec::DMCmd &msg)
      {
        return;
      }
    }
  }
}
#endif
