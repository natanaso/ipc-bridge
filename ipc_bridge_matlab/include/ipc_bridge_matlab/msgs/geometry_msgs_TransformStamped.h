#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM_STAMPED__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM_STAMPED__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_TransformStamped.h>

#include <ipc_bridge_matlab/msgs/roslib_Header.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_Transform.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace TransformStamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::TransformStamped &msg)
      {
        const char *fields[] = {"header", "child_frame_id", "transform"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));

      if (msg.child_frame_id == 0)
        {
          char buf[1] = "";
          mxSetField(out, 0, "child_frame_id", mxCreateString(buf));
        }
      else
        {
          char buf[strlen(msg.child_frame_id) + 1];
          strcpy(buf, msg.child_frame_id);
          mxSetField(out, 0, "child_frame_id", mxCreateString(buf));
        }

        mxSetField(out, 0, "transform", 
                   ipc_bridge_matlab::geometry_msgs::Transform::ProcessMessage(msg.transform));

        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::TransformStamped &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "child_frame_id");     
        int buflen = 128;
        char buf[buflen];
        mxGetString(field, buf, buflen);
        if (strlen(buf) > 0)
          {
            msg.child_frame_id = new char[strlen(buf) + 1];
            strcpy(msg.child_frame_id, buf);
          }

        field = mxGetField(a, 0, "transform");
        ipc_bridge_matlab::geometry_msgs::Transform::ProcessArray(field, msg.transform);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::TransformStamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        if (msg.child_frame_id != 0)
          {
            delete[] msg.child_frame_id;
            msg.child_frame_id = 0;
          }
        ipc_bridge_matlab::geometry_msgs::Transform::Cleanup(msg.transform);
      }
    }
  }
}
#endif
