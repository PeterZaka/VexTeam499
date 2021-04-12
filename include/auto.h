#pragma once

/*

- Smart pointers
- Don't use global variables - make some local and some static
- For checking if driveForward or turnTo is done, check
if PID's error is below certain threshold or if one of the motor's
velocity is below certain threshold - eliminates some variables,
easier to read, less copy and paste code (updateCloseEnoughDeg, updateCloseEnoughRot)

*/

#include <cmath> // std::abs
#include "vex.h"
#include "inertial.h"
#include "pid.h"
#include "motors.h"
#include "odom.h"

#define PI 3.14159265

namespace team499 {

  enum unit {
    degrees = 1,
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
  extern double target;
  extern double leftMotorError;
  extern double rightMotorError;
  extern double targetRot;

  extern double leftMotorPower;
  extern double rightMotorPower;

  extern vex::motor* LeftWheelMotor;
  extern vex::motor* RightWheelMotor;

  // auto functions
  void driveForward(double amount, unit units);

  void turnTo(double amount);

  // only in inches
  void goTo(double x, double y);

  // definitely need better name
  void resetCloseEnoughs();
  void updateCloseEnoughDeg();
  void updateCloseEnoughRot();


  // helper functions
  // beginning of all auto functions
  void resetAuto();

  // used to go straight
  void correctRobot();
}