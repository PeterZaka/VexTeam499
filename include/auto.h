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

  // editable

  extern double maxPower;

  extern int targetTime;
  extern double closeEnoughDeg;
  extern double closeEnoughRot;


  const int defaultTargetTime = targetTime;
  const double defaultCloseEnoughDeg = closeEnoughDeg;
  const double defaultCloseEnoughRot = closeEnoughRot;

  extern int timeOnTarget;
  extern int prevTime;
  extern double averageEncoder;
  extern double prevEncoder;
  extern double leftMotorError;
  extern double rightMotorError;
  extern double targetRot;

  extern double leftMotorPower;
  extern double rightMotorPower;

  extern vex::motor* LeftWheelMotor;
  extern vex::motor* RightWheelMotor;

  // auto functions
  void driveForward();
  void driveForward(double amount, unit units);

  void turnTo(double amount);

  // only in inches
  void goTo(double x, double y, unit units);

  // definitely need better name
  void resetCloseEnoughs();
  void updateCloseEnoughDeg(const double& target);
  void updateCloseEnoughRot(const double& target);


  // helper functions
  // beginning of all auto functions
  void resetAuto();

  // used to go straight
  void correctRobot();
}