#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT_STAMPED__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT_STAMPED__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_PointStamped.h>

#include <rosgraph_msgs_Header.h>
#include <geometry_msgs_Point.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace PointStamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::PointStamped &msg)
      {
        const char *fields[] = {"header", "point"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "point",
                   ipc_bridge_matlab::geometry_msgs::Point::ProcessMessage(msg.point));

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::geometry_msgs::PointStamped &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "point");
        ipc_bridge_matlab::geometry_msgs::Point::ProcessArray(field, msg.point);

        return SUCCESS;
      }
      static void Cleanup(ipc_bridge::geometry_msgs::PointStamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::Point::Cleanup(msg.point);

        return;
      }
    }
  }
}
#endif
