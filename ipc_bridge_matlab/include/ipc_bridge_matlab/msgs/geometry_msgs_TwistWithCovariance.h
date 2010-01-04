#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST_WITH_COVARIANCE__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TWIST_WITH_COVARIANCE__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_TwistWithCovariance.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_Twist.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace TwistWithCovariance
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::TwistWithCovariance &msg)
      {
        const char *fields[] = {"twist", "covariance"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "twist", 
                   ipc_bridge_matlab::geometry_msgs::Twist::ProcessMessage(msg.twist));

        mxArray *covariance = mxCreateDoubleMatrix(1, 36, mxREAL);
        std::copy(msg.covariance, msg.covariance + 36,
                  mxGetPr(covariance));
        mxSetField(out, 0, "covariance", covariance);
        
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::TwistWithCovariance &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "twist");
        ipc_bridge_matlab::geometry_msgs::Twist::ProcessArray(field, msg.twist);

        field = mxGetField(a, 0, "covariance");
        ipc_bridge_matlab::GetDoubleArray(field, 36, msg.covariance);
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::TwistWithCovariance &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Twist::Cleanup(msg.twist);
        return;
      }
    }
  }
}
#endif
