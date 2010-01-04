#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Transform.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Vector3.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_Quaternion.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Transform
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Transform &msg)
      {
        const char *fields[] = {"translation", "rotation"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "translation", 
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.translation));
        mxSetField(out, 0, "rotation", 
                   ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessMessage(msg.rotation));

        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::Transform &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "translation");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.translation);

        field = mxGetField(a, 0, "rotation");
        ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessArray(field, msg.rotation);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Transform &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.translation);
        ipc_bridge_matlab::geometry_msgs::Quaternion::Cleanup(msg.rotation);
      }
    }
  }
}
#endif
