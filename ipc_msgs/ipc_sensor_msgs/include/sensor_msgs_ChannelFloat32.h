#ifndef __IPC_BRIDGE_MATLAB_SENSOR_MSGS_CHANNELFLOAT32__
#define __IPC_BRIDGE_MATLAB_SENSOR_MSGS_CHANNELFLOAT32__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/sensor_msgs_ChannelFloat32.h>

namespace ipc_bridge_matlab
{
  namespace sensor_msgs
  {
    namespace ChannelFloat32
    {
      static mxArray* ProcessMessage(const ipc_bridge::sensor_msgs::ChannelFloat32 &msg)
      {
        const char *fields[] = {"name", 
                                "values"};
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

        int length = msg.values_length;
        mxArray *values = mxCreateDoubleMatrix(1, length, mxREAL);
        std::copy(msg.values, msg.values + length, mxGetPr(values));
        mxSetField(out, 0, "values", values);
                                 
        return out;
      }
      
      static int ProcessArray(const mxArray *a, ipc_bridge::sensor_msgs::ChannelFloat32 &msg)
      {
        mxArray *field;
        
        field = mxGetField(a, 0, "name");     
        
        int buflen = 128;
        char buf[buflen];
        mxGetString(field, buf, buflen);
        if (strlen(buf) > 0)
          {
            msg.name = new char[strlen(buf) + 1];
            strcpy(msg.name, buf);
          }

        field = mxGetField(a, 0, "values");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.values_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.values_length = 0;
            msg.values = 0;
          }

        if (msg.values_length > 0)
          {
            double *p = mxGetPr(field);
            msg.values = new float[msg.values_length];
            std::copy(p, p + msg.values_length, msg.values);
          }
        
        return SUCCESS;
      }    

      static void Cleanup(ipc_bridge::sensor_msgs::ChannelFloat32 &msg)
      {
        if (msg.name != 0)
          {
            delete[] msg.name;
            msg.name = 0;
          }

        if (msg.values != 0)
          {
            delete[] msg.values;
            msg.values_length = 0;
            msg.values = 0;
          }

        return;
      }
    }
  }
}
#endif
