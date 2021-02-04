#pragma once

#include <cmath> // std::abs
#include "vex.h"
#include "inertial.h"
#include "pid.h"

#define PI 3.14159265

namespace team499 {

  const double wheelDiameter = 1;
  const double circumference = wheelDiameter * PI;
  const double degreesToRadians = PI / 180;

  enum unit {
    degrees = 1,
    inches = (int)(circumference * 360),
    boxes = inches * 5
  };

  extern int targetTime;
  extern int timeOnTarget;
  extern int prevTime;

  extern int closeEnoughDeg;
  extern int closeEnoughRot;

  extern double prevLeft;

  const int defaultTargetTime = targetTime;
  const int defaultCloseEnoughDeg = closeEnoughDeg;
  const int defaultCloseEnoughRot = closeEnoughRot;

  const double maxPower = 100;

  extern vex::motor* LeftWheelMotor;
  extern vex::motor* RightWheelMotor;

  // auto functions

  void driveForward(double amount, unit units);

  void turnTo(double amount);

  // only in inches
  void goTo(double x, double y, unit units);

  // definitely need better name
  void resetCloseEnoughs();
  void updateCloseEnoughDeg(const double& target);
  void updateCloseEnoughRot(const double& target);
}