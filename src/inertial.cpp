#include "inertial.h"

namespace team499{

  double xPos = 0;
  double yPos = 0;
  double rot = 0;

  bool isCalibrated = false;
  bool canceledCalibration = false;

  void calibrateInertial()
  {
    iSensor.calibrate();
    while(iSensor.isCalibrating())
    {
      if(Controller1.ButtonA.pressing())
      {
        canceledCalibration = true;
        return;
      }
      resetScreen();
      printOnController("CALIBRATING");
      wait(50, msec);
    }
    wait(20, msec);

    resetScreen();
    printOnController("Finished calibration");

    isCalibrated = true;
  }

  void updatePosition()
  {
    xPos += iSensor.acceleration(xaxis);
    yPos += iSensor.acceleration(yaxis);
  }

  void updateRotation()
  {
    rot = iSensor.rotation();
  }

  void updateInertial()
  {
    if(isCalibrated)
    {
      updatePosition();
      updateRotation();
    }
  }

  void updateInertialForever()
  {
    if(!isCalibrated)
    {
      return;
    }
    while(true)
    {
      updateInertial();
      wait(20, msec);
    }
  }

}