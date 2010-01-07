#ifndef __IPC_BRIDGE_MATLAB_NAV_MSGS_ODOMETRY__
#define __IPC_BRIDGE_MATLAB_NAV_MSGS_ODOMETRY__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_Odometry.h>

#include <ipc_bridge_matlab/msgs/roslib_Header.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_PoseWithCovariance.h>
#include <ipc_bridge_matlab/msgs/geometry_msgs_TwistWithCovariance.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace Odometry
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::Odometry &msg)
      {
        const char *fields[] = {"header", 
                                "child_frame_id", 
                                "pose",
                                "twist"};
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

        mxSetField(out, 0, "pose", 
                   ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::ProcessMessage(msg.pose));
        mxSetField(out, 0, "twist", 
                   ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::ProcessMessage(msg.twist));

        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::nav_msgs::Odometry &msg)
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

        field = mxGetField(a, 0, "pose");
        ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::ProcessArray(field, 
                                                                        msg.pose);

        field = mxGetField(a, 0, "twist");
        ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::ProcessArray(field, 
                                                                         msg.twist);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::Odometry &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::Cleanup(msg.pose);
        ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::Cleanup(msg.twist);
        if (msg.child_frame_id != 0)
          {
            delete[] msg.child_frame_id;
            msg.child_frame_id = 0;
          }
      }
    }
  }
}
#endif
