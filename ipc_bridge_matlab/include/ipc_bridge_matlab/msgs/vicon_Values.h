#ifndef __IPC_BRIDGE_MATLAB_VICON_VALUES__
#define __IPC_BRIDGE_MATLAB_VICON_VALUES__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/vicon_Values.h>

#include <ipc_bridge_matlab/msgs/roslib_Header.h>

namespace ipc_bridge_matlab
{
  namespace vicon
  {
    namespace Values
    {
      static mxArray* ProcessMessage(const ipc_bridge::vicon::Values &msg)
      {
        const char *fields[] = {"header", 
                                "values"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        
        int length = msg.values_length;
        mxArray *values = mxCreateDoubleMatrix(1, length, mxREAL);
        std::copy(msg.values, msg.values + length, mxGetPr(values));
        mxSetField(out, 0, "values", values);
          
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::vicon::Values &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

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
            msg.values = new double[msg.values_length];
            std::copy(p, p + msg.values_length, msg.values);
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::vicon::Values &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        if (msg.values != 0)
          {
            delete[] msg.values;
            msg.values_length = 0;
            msg.values = 0;
          }
      }
    }
  }
}
#endif
