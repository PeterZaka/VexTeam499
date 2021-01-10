#pragma once

#include "motorGroup.h"
#include "inertial.h"
#include "pid.h"

namespace team499{
  
  extern double straightRot;
  extern bool isDrivingStraight;

  extern double turnDirection;
  extern bool isTurning;

  // use after UpdateAllMotors()
  void driveStraight(motorGroup* left, motorGroup* right);

  void turnToButton();
}