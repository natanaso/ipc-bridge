#ifndef __IPC_BRIDGE_MATLAB_ROSLIB_HEADER__
#define __IPC_BRIDGE_MATLAB_ROSLIB_HEADER__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/roslib_Header.h>

namespace ipc_bridge_matlab
{
  namespace Header
  {
    static mxArray* ProcessMessage(const ipc_bridge::Header &msg)
    {
      const char *fields[] = {"seq", 
                              "stamp", 
                              "frame_id"};
      const int nfields = sizeof(fields)/sizeof(*fields);
      mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

      mxSetField(out, 0, "seq", mxCreateDoubleScalar(msg.seq));
      mxSetField(out, 0, "stamp", mxCreateDoubleScalar(msg.stamp));

      if (msg.frame_id == 0)
        {
          char buf[1] = "";
          mxSetField(out, 0, "frame_id", mxCreateString(buf));
        }
      else
        {
          char buf[strlen(msg.frame_id) + 1];
          strcpy(buf, msg.frame_id);
          mxSetField(out, 0, "frame_id", mxCreateString(buf));
        }

      return out;
    }
    
    static int ProcessArray(const mxArray *a, ipc_bridge::Header &msg)
    {
      mxArray *field;

      field = mxGetField(a, 0, "seq");
      msg.seq = mxGetScalar(field);

      field = mxGetField(a, 0, "stamp");
      msg.stamp = mxGetScalar(field);

      field = mxGetField(a, 0, "frame_id");     
      
      int buflen = 128;
      char buf[buflen];
      mxGetString(field, buf, buflen);
      if (strlen(buf) > 0)
        {
          msg.frame_id = new char[strlen(buf) + 1];
          strcpy(msg.frame_id, buf);
        }
      
      return SUCCESS;
    }

    static void Cleanup(ipc_bridge::Header &msg)
    {
      if (msg.frame_id != 0)
        {
          delete[] msg.frame_id;
          msg.frame_id = 0;
        }
    }
  }
}
#endif
