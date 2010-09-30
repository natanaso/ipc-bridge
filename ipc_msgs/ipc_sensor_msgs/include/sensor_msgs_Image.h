#ifndef __IPC_BRIDGE_MATLAB_SENSOR_MSGS_IMAGE__
#define __IPC_BRIDGE_MATLAB_SENSOR_MSGS_IMAGE__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/sensor_msgs_Image.h>

#include <roslib_Header.h>

namespace ipc_bridge_matlab
{
  namespace sensor_msgs
  {
    namespace Image
    {
      static mxArray* ProcessMessage(const ipc_bridge::sensor_msgs::Image &msg)
      {
        const char *fields[] = {"header", 
                                "height", 
                                "width", 
                                "encoding", 
                                "is_bigendian",
                                "step", 
                                "data"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "height", mxCreateDoubleScalar(msg.height));
        mxSetField(out, 0, "width", mxCreateDoubleScalar(msg.width));
        if (msg.encoding == 0)
          {
            char buf[1] = "";
            mxSetField(out, 0, "encoding", mxCreateString(buf));
          }
        else
          {
            char buf[strlen(msg.encoding) + 1];
            strcpy(buf, msg.encoding);
            mxSetField(out, 0, "encoding", mxCreateString(buf));
          }
        mxSetField(out, 0, "is_bigendian", mxCreateDoubleScalar(msg.is_bigendian));
        mxSetField(out, 0, "step", mxCreateDoubleScalar(msg.step));
       
        int length = msg.data_length;
        mxArray *data = mxCreateDoubleMatrix(1, length, mxREAL);
        std::copy(msg.data, msg.data + length, mxGetPr(data));
        mxSetField(out, 0, "data", data);
          
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::sensor_msgs::Image &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        msg.height = mxGetScalar(mxGetField(a, 0, "height"));
        msg.width = mxGetScalar(mxGetField(a, 0, "width"));

        field = mxGetField(a, 0, "encoding");     
        
        int buflen = 128;
        char buf[buflen];
        mxGetString(field, buf, buflen);
        if (strlen(buf) > 0)
          {
            msg.encoding = new char[strlen(buf) + 1];
            strcpy(msg.encoding, buf);
          }

        msg.is_bigendian = mxGetScalar(mxGetField(a, 0, "is_bigendian"));
        msg.step = mxGetScalar(mxGetField(a, 0, "step"));

        field = mxGetField(a, 0, "data");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.data_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.data_length = 0;
            msg.data = 0;
          }

        if (msg.data_length > 0)
          {
            double *p = mxGetPr(field);
            msg.data = new unsigned char[msg.data_length];
            std::copy(p, p + msg.data_length, msg.data);
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::sensor_msgs::Image &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);

        if (msg.encoding != 0)
        {
          delete[] msg.encoding;
          msg.encoding = 0;
        }

        if (msg.data != 0)
          {
            delete[] msg.data;
            msg.data_length = 0;
            msg.data = 0;
          }
      }
    }
  }
}
#endif
