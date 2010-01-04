#ifndef __IPC_BRIDGE_MATLAB_NAV_MSGS_MAP_META_DATA__
#define __IPC_BRIDGE_MATLAB_NAV_MSGS_MAP_META_DATA__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_MapMetaData.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Pose.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace MapMetaData
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        const char *fields[] = {"map_load_time", 
                                "resolution", 
                                "width", 
                                "height",
                                "origin"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "map_load_time", mxCreateDoubleScalar(msg.map_load_time));
        mxSetField(out, 0, "resolution", mxCreateDoubleScalar(msg.resolution));
        mxSetField(out, 0, "width", mxCreateDoubleScalar(msg.width));
        mxSetField(out, 0, "height", mxCreateDoubleScalar(msg.height));
        mxSetField(out, 0, "origin", 
                   ipc_bridge_matlab::geometry_msgs::Pose::ProcessMessage(msg.origin));

        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "map_load_time");
        msg.map_load_time = mxGetScalar(field);

        field = mxGetField(a, 0, "resolution");
        msg.resolution = mxGetScalar(field);

        field = mxGetField(a, 0, "width");
        msg.width = mxGetScalar(field);

        field = mxGetField(a, 0, "height");
        msg.height = mxGetScalar(field);

        field = mxGetField(a, 0, "origin");
        ipc_bridge_matlab::geometry_msgs::Pose::ProcessArray(field, msg.origin);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Pose::Cleanup(msg.origin);
      }
    }
  }
}
#endif
