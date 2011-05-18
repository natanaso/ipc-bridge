#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSG_VECTOR3STAMPED__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSG_VECTOR3STAMPED__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Vector3Stamped.h>

#include <rosgraph_msgs_Header.h>
#include <geometry_msgs_Vector3.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Vector3Stamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Vector3Stamped &msg)
      {
        const char *fields[] = {"header", "vector"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "vector",
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.vector));

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Vector3Stamped &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "vector");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.vector);

        return SUCCESS;
      }
      static void Cleanup(ipc_bridge::geometry_msgs::Vector3Stamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.vector);

        return;
      }
    }
  }
}
#endif
