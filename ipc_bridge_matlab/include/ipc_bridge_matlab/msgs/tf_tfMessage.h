#ifndef __IPC_BRIDGE_MATLAB_SENSOR_MSGS_LASER_SCAN__
#define __IPC_BRIDGE_MATLAB_SENSOR_MSGS_LASER_SCAN__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/tf_tfMessage.h>

#include <ipc_bridge_matlab/msgs/geometry_msgs_TransformStamped.h>

namespace ipc_bridge_matlab
{
  namespace tf
  {
    namespace tfMessage
    {
      static mxArray* ProcessMessage(const ipc_bridge::tf::tfMessage &msg)
      {
        const char *fields[] = {"transforms"}; 
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        const int length = msg.transforms_length;      
        mxArray *transforms = mxCreateCellArray(1, &length);
        for (unsigned int i = 0; i < length; i++)
          mxSetCell(transforms, i, 
                    ipc_bridge_matlab::geometry_msgs::TransformStamped::ProcessMessage(msg.transforms[i]));
        mxSetField(out, 0, "transforms", transforms);
         
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::tf::tfMessage &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "transforms");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.transforms_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.transforms_length = 0;
            msg.transforms = 0;
          }

        if (msg.transforms_length > 0)
          {
            msg.transforms = new geometry_msgs_TransformStamped[msg.transforms_length];
            for (unsigned int i = 0; i < msg.transforms_length; i++)
              {
                mxArray *p = mxGetCell(field, i);
                ipc_bridge_matlab::geometry_msgs::TransformStamped::ProcessArray(p, msg.transforms[i]);
              }
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::tf::tfMessage &msg)
      {
        for (unsigned int i = 0; i < msg.transforms_length; i++)
          ipc_bridge_matlab::geometry_msgs::TransformStamped::Cleanup(msg.transforms[i]);
        if (msg.transforms != 0)
          {
            delete[] msg.transforms;
            msg.transforms_length = 0;
            msg.transforms = 0;
          }
      }
    }
  }
}
#endif
