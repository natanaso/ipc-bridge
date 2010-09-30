#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_WRENCH__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_WRENCH__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Wrench.h>

#include <geometry_msgs_Vector3.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Wrench
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Wrench &msg)
      {
        const char *fields[] = {"force", "torque"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "force", 
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.force));
        mxSetField(out, 0, "torque", 
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.torque));
        
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::Wrench &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "force");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.force);

        field = mxGetField(a, 0, "torque");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.torque);
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Wrench &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.force);
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.torque);
        return;
      }
    }
  }
}
#endif
