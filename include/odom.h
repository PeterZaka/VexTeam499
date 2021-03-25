#pragma once

#include <math.h>
#include "motors.h"
#include "robot-config.h"

namespace team499{

  extern double xPos;
  extern double yPos;
  extern double rotInRadian;

  extern double xPosWithRot;
  extern double yPosWithRot;
  extern double prevRotInRadian;

  void calculateOdom();

  void odomThreadFunc();

};