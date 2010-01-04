#include <ipc_bridge_matlab/ipc_bridge_matlab.h>

#define DATA_HANDLER ipc_bridge_matlab::MESSAGE_NAME::ProcessMessage
#define ARRAY_HANDLER ipc_bridge_matlab::MESSAGE_NAME::ProcessArray
#define CLEANUP_HANDLER ipc_bridge_matlab::MESSAGE_NAME::Cleanup

ipc_bridge_matlab::Interface<ipc_bridge::MESSAGE_NAME> interface(DATA_HANDLER, ARRAY_HANDLER, CLEANUP_HANDLER);

extern "C" 
{
  void mexExit()
  {
    interface.Finalize();
    return;
  }

  void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
  {
    // Register the exit function
    mexAtExit(mexExit);

    // Verify the input is good, something must be given
    if (nrhs == 0) 
      {
        mexWarnMsgTxt("Need input argument");
        plhs[0] = mxCreateDoubleScalar(-1);
        return;
      }

    int buflen = 128;
    char buf[buflen];
    
    // Check to see that we can read the input string
    if (mxGetString(prhs[0], buf, buflen) != 0) 
      {
        mexWarnMsgTxt("Could not read string.");
        plhs[0] = mxCreateDoubleScalar(-1);
        return;
      }

    // Now hand it off to the class object which will
    // do the real work
    int out;
    switch (out = interface.ProcessCall(nlhs, plhs, nrhs, prhs))
      {
      case EXIT:
        mexExit();
        plhs[0] = mxCreateDoubleScalar(0);
        return;
      case NOOVERWRITE:
        return;
      case ERROR_INPUT:
        mexWarnMsgTxt("Incorrect Input.");
        plhs[0] = mxCreateDoubleScalar(-1);
        return;
      case ERROR_FAILED:
        mexWarnMsgTxt("Input Failed.");
        plhs[0] = mxCreateDoubleScalar(-1);
        return;
      case ERROR_UNHANDLED:
        mexWarnMsgTxt("Unhandled Input.");
        plhs[0] = mxCreateDoubleScalar(-1);
        return;
      default:
        plhs[0] = mxCreateDoubleScalar(out);
        return;
      }
  }
}
