#ifndef __IPC_BRIDGE_MATLAB_SENSOR_MSGS_LASER_SCAN__
#define __IPC_BRIDGE_MATLAB_SENSOR_MSGS_LASER_SCAN__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/sensor_msgs_LaserScan.h>

#include <roslib_Header.h>

namespace ipc_bridge_matlab
{
  namespace sensor_msgs
  {
    namespace LaserScan
    {
      static mxArray* ProcessMessage(const ipc_bridge::sensor_msgs::LaserScan &msg)
      {
        const char *fields[] = {"header", 
                                "angle_min", 
                                "angle_max", 
                                "angle_increment", 
                                "time_increment",
                                "scan_time", 
                                "range_min",
                                "range_max",
                                "ranges",
                                "intensities"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "angle_min", mxCreateDoubleScalar(msg.angle_min));
        mxSetField(out, 0, "angle_max", mxCreateDoubleScalar(msg.angle_max));
        mxSetField(out, 0, "angle_increment", mxCreateDoubleScalar(msg.angle_increment));
        mxSetField(out, 0, "time_increment", mxCreateDoubleScalar(msg.time_increment));
        mxSetField(out, 0, "scan_time", mxCreateDoubleScalar(msg.scan_time));
        mxSetField(out, 0, "range_min", mxCreateDoubleScalar(msg.range_min));
        mxSetField(out, 0, "range_max", mxCreateDoubleScalar(msg.range_max));
        
        int length = msg.ranges_length;
        mxArray *ranges = mxCreateDoubleMatrix(1, length, mxREAL);
        std::copy(msg.ranges, msg.ranges + length, mxGetPr(ranges));
        mxSetField(out, 0, "ranges", ranges);

        length = msg.intensities_length;
        mxArray *intensities = mxCreateDoubleMatrix(1, length, mxREAL);
        std::copy(msg.intensities, msg.intensities + length, mxGetPr(intensities));
        mxSetField(out, 0, "intensities", intensities);
          
        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::sensor_msgs::LaserScan &msg)
      {
        mxArray *field;       

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        msg.angle_min = mxGetScalar(mxGetField(a, 0, "angle_min"));
        msg.angle_max = mxGetScalar(mxGetField(a, 0, "angle_max"));
        msg.angle_increment = mxGetScalar(mxGetField(a, 0, "angle_increment"));
        msg.time_increment = mxGetScalar(mxGetField(a, 0, "time_increment"));
        msg.scan_time = mxGetScalar(mxGetField(a, 0, "scan_time"));
        msg.range_min = mxGetScalar(mxGetField(a, 0, "range_min"));
        msg.range_max = mxGetScalar(mxGetField(a, 0, "range_max"));

        field = mxGetField(a, 0, "ranges");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.ranges_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.ranges_length = 0;
            msg.ranges = 0;
          }

        if (msg.ranges_length > 0)
          {
            double *p = mxGetPr(field);
            msg.ranges = new float[msg.ranges_length];
            std::copy(p, p + msg.ranges_length, msg.ranges);
          }

        field = mxGetField(a, 0, "intensities");
        nrows = mxGetM(field);
        ncols = mxGetN(field);

        length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.intensities_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.intensities_length = 0;
            msg.intensities = 0;
          }

        if (msg.intensities_length > 0)
          {
            double *p = mxGetPr(field);
            msg.intensities = new float[msg.intensities_length];
            std::copy(p, p + msg.intensities_length, msg.intensities);
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::sensor_msgs::LaserScan &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        if (msg.ranges != 0)
          {
            delete[] msg.ranges;
            msg.ranges_length = 0;
            msg.ranges = 0;
          }
        if (msg.intensities != 0)
          {
            delete[] msg.intensities;
            msg.intensities_length = 0;
            msg.intensities = 0;
          }
      }
    }
  }
}
#endif
