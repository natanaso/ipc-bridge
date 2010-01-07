#ifndef __IPC_BRIDGE_MATLAB_VICON_NAMES__
#define __IPC_BRIDGE_MATLAB_VICON_NAMES__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/vicon_Names.h>

namespace ipc_bridge_matlab
{
  namespace vicon
  {
    namespace Names
    {
      static mxArray* ProcessMessage(const ipc_bridge::vicon::Names &msg)
      {
        const char *fields[] = {"names"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        int length = msg.names_length;
        mxArray *names = mxCreateCellMatrix(1, length);
        if (msg.names != 0)
          {
            for (int i = 0; i < length; i++)
              {               
                if (msg.names[i] != 0)
                  {
                    char buf[strlen(msg.names[i])+1];
                    strcpy(buf, msg.names[i]);
                    mxSetCell(names, i, mxCreateString(buf));            
                  }
                else
                  {
                    char buf[1] = "";
                    mxSetCell(names, i, mxCreateString(buf));            
                  }
              }
          }
        mxSetField(out, 0, "names", names);
          
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::vicon::Names &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "names");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.names_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.names_length = 0;
            msg.names = 0;
          }

        if (msg.names_length > 0)
          {
            for (unsigned int i = 0; i < msg.names_length; i++)
              {
                mxArray *c = mxGetCell(field, i);
                char buf[264];
                mxGetString(c, buf, 264);
                msg.names[i] = new char[strlen(buf) + 1];
                strcpy(msg.names[i], buf);
              }
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::vicon::Names &msg)
      {
        if (msg.names != 0)
          {
            for (unsigned int i = 0; i < msg.names_length; i++)
              delete[] msg.names[i];

            msg.names_length = 0;
            msg.names = 0;
          }
      }
    }
  }
}
#endif
