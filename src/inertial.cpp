#include "inertial.h"

namespace team499{

  double xPos = 0;
  double yPos = 0;
  double rot = 0;

  void calibrateInertial()
  {
    iSensor.calibrate();
    while(iSensor.isCalibrating())
    {
      resetScreen();
      printOnController("CALIBRATING");
      wait(50, msec);
    }
    resetScreen();
    printOnController("Finished calibration");
  }

  void updatePosition()
  {
    xPos += iSensor.acceleration(xaxis);
    yPos += iSensor.acceleration(yaxis);
  }

  void updateRotation()
  {
    rot = iSensor.heading();
  }

  void updateInertialForever()
  {
    while(true)
    {
      updatePosition();
      updateRotation();
      wait(20, msec);
    }
  }

}