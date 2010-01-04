#ifndef __IPC_BRIDGE_MATLAB_ASCTEC_VOLTAGE__
#define __IPC_BRIDGE_MATLAB_ASCTEC_VOLTAGE__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/asctec_Voltage.h>

#include <ipc_bridge_matlab/msgs/roslib_Header.h>

namespace ipc_bridge_matlab
{
  namespace asctec
  {
    namespace Voltage
    {
      static mxArray* ProcessMessage(const ipc_bridge::asctec::Voltage &msg)
      {
        const char *fields[] = {"header", 
                                "battery_voltage"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        
        mxSetField(out, 0, "battery_voltage", 
                   mxCreateDoubleScalar(msg.battery_voltage));
       
        return out;
      }
    
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::asctec::Voltage &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);
        
        field = mxGetField(a, 0, "battery_voltage");
        msg.battery_voltage = mxGetScalar(field);
     
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::asctec::Voltage &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
      }
    }
  }
}
#endif
