#pragma once

#include <cmath> // std::abs
#include "vex.h"
#include "inertial.h"
#include "pid.h"

#define PI 3.14159265

namespace team499 {

  extern double xPos;
  extern double yPos;

  const double wheelDiameter = 1;
  const double circumference = wheelDiameter * PI;
  const double degreesToRadians = PI / 180;

  enum unit {
    degrees = 1,
    inches = (int)(circumference * 360),
    boxes = inches * 5
  };

  extern int targetTime;
  extern int closeEnoughDegrees;
  extern int closeEnoughDegreesRot;

  const double maxPower = 90;

  extern vex::motor* LeftWheelMotor;
  extern vex::motor* RightWheelMotor;

  // auto functions

  void driveForwardPID(double amount, unit units);

  void driveForward(double amount, unit units);

  void turnTo(double amount);

  // only in inches
  void goTo(double x, double y, unit units);
}