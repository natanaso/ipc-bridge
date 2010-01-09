#ifndef __IPC_BRIDGE_MATLAB_VICON_SUBJECT__
#define __IPC_BRIDGE_MATLAB_VICON_SUBJECT__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/vicon_Subject.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Pose.h>

namespace ipc_bridge_matlab
{
  namespace vicon
  {
    namespace Subject
    {
      static mxArray* ProcessMessage(const ipc_bridge::vicon::Subject &msg)
      {
        const char *fields[] = {"name", 
                                "pose"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        if (msg.name == 0)
          {
            char buf[1] = "";
            mxSetField(out, 0, "name", mxCreateString(buf));
          }
        else
          {
            char buf[strlen(msg.name) + 1];
            strcpy(buf, msg.name);
            mxSetField(out, 0, "name", mxCreateString(buf));
          }

        mxSetField(out, 0, "pose", 
                   ipc_bridge_matlab::geometry_msgs::Pose::ProcessMessage(msg.pose));
          
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::vicon::Subject &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "pose");
        ipc_bridge_matlab::geometry_msgs::Pose::ProcessArray(field, msg.pose);

        field = mxGetField(a, 0, "name");     
        
        int buflen = 128;
        char buf[buflen];
        mxGetString(field, buf, buflen);
        if (strlen(buf) > 0)
          {
            msg.name = new char[strlen(buf) + 1];
            strcpy(msg.name, buf);
          }       

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::vicon::Subject &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Pose::Cleanup(msg.pose);
        if (msg.name != 0)
          {
            delete[] msg.name;
            msg.name = 0;
          }
      }
    }
  }
}
#endif
