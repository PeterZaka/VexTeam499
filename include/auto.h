#pragma once

#include <cmath> // std::abs
#include "vex.h"
#include "inertial.h"
#include "pid.h"

namespace team499{

  enum unit{
    degrees = 1,
    inches = 12,
    boxes = 500
  };

  const int targetTime = 100; // in msec
  const int closeEnoughDegrees = 10;
  const int closeEnoughDegreesRot = 3;

  const double maxPower = 80;

  extern vex::motor LeftWheelMotor;
  extern vex::motor RightWheelMotor;

  // auto functions

  void driveForwardPID(double amount, unit units);

  void driveForward(double amount, unit units);

  void turnTo(double amount);
}