#pragma once

#include "vex.h"
#include "common.h"

namespace team499 {

  extern double xPos;
  extern double yPos;
  extern double rot;

  void calibrateInertial();

  void updatePosition();

  void updateRotation();

  void updateInertialForever();

}