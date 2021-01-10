#pragma once

#include "motorGroup.h"
#include "inertial.h"

namespace team499{
  
  extern double straightRot;
  extern bool isDrivingStraight;

  // use after UpdateAllMotors()
  void driveStraight(motorGroup* left, motorGroup* right);
}