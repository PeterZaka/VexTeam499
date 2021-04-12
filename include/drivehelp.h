#pragma once

/*

- Use static variables because all/most variables are only used in this file
(I haven't used static variables much so idk if that's the best choice)

*/

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