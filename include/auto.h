#pragma once

#include <cmath> // std::abs
#include "vex.h"
#include "inertial.h"

namespace team499{

  enum unit{
    degrees = 1,
    inches = 12,
    boxes = 500
  };

  const int targetTime = 100;
  const int closeEnoughDegrees = 10;
  const int closeEnoughDegreesRot = 2;

  const double maxPower = 80;
  const double slowDown = 0.2;
  const double slowDownRot = 3;

  extern vex::motor LeftWheelMotor;
  extern vex::motor RightWheelMotor;

  // auto functions

  void driveForwardPID(double amount, unit units);

  void driveForwardInertial(double amount, unit units);

  void turnToInertial(double amount);
}