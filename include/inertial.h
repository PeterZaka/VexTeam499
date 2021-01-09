#pragma once

#include "vex.h"
#include "common.h"

namespace team499 {

  extern double xPos;
  extern double yPos;
  extern double rot;
  
  extern bool isCalibrated;
  extern bool canceledCalibration;

  void calibrateInertial();

  void updatePosition();

  void updateRotation();

  void updateInertial();

  void updateInertialForever();

}