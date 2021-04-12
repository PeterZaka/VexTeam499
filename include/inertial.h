#pragma once

/*

- rotCorrection should not be here. It is used for autonomous

*/

#include "vex.h"
#include "common.h"

namespace team499 {

  const double rotCorrection = 10;

  extern double xAcc;
  extern double yAcc;
  extern double rot;
  
  extern bool isCalibrated;
  extern bool canceledCalibration;

  void calibrateInertial();

  void updatePosition();

  void updateRotation();

  void updateInertial();

  void updateInertialForever();

}