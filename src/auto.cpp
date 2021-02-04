#include "auto.h"

namespace team499 {

  int targetTime = 40; // in msec
  int closeEnoughDeg = 30;
  int closeEnoughRot = 2;

  double prevLeft = 0;

  int timeOnTarget = 0;
  int prevTime = 0;

  void driveForward(double amount, unit units)
  {
    amount *= units;

    timeOnTarget = 0;
    double targetRot = rot;

    double leftMotorPower;
    double rightMotorPower;

    double leftMotorError;
    double rightMotorError;

    LeftPID.reset();
    RightPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    prevTime = timer::system();

    while (timeOnTarget < targetTime)
    {
      //resetScreen();
      //printOnController("encoder", LeftWheelMotor->position(deg));

      // adjust to go straight
      if (rot - 0.2 > targetRot) // rotated to the right
      {
        leftMotorError = targetRot - rot;
        rightMotorError = rot - targetRot;
      }
      else if (rot + 0.2 < targetRot) // rotated to the left
      {
        leftMotorError = rot - targetRot;
        rightMotorError = targetRot - rot;
      }
      else
      {
        leftMotorError = 0;
        rightMotorError = 0;
      }

      // calculate PID
      leftMotorPower = LeftPID.update(LeftWheelMotor->position(deg), amount);
      rightMotorPower = RightPID.update(RightWheelMotor->position(deg), amount);

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower + leftMotorError * rotCorrection, pct);
      RightWheelMotor->spin(fwd, rightMotorPower + rightMotorError * rotCorrection, pct);

      updateCloseEnoughDeg(amount);

      prevTime = timer::system();
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void turnTo(double targetRot)
  {
    timeOnTarget = 0;
    targetRot = quickestRotation(rot, targetRot);

    double leftMotorPower;
    double rightMotorPower;

    LeftTurnPID.reset();
    RightTurnPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    prevTime = timer::system();

    while (timeOnTarget < targetTime)
    {
      //resetScreen();
      //printOnController("rot", rot);

      // calculate PID
      leftMotorPower = LeftTurnPID.update(rot, targetRot);
      rightMotorPower = -RightTurnPID.update(rot, targetRot);

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, rightMotorPower, pct);

      updateCloseEnoughRot(targetRot);

      prevTime = timer::system();
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void resetCloseEnoughs()
  {
    targetTime = defaultTargetTime;
    closeEnoughDeg = defaultCloseEnoughDeg;
    closeEnoughRot = defaultCloseEnoughRot;
  }

  void updateCloseEnoughDeg(const double& target)
  {
    if (fabs(LeftWheelMotor->position(deg) - target) <= closeEnoughDeg || LeftWheelMotor->position(deg) == prevLeft)
    {
      timeOnTarget += timer::system() - prevTime;
    }
    else
    {
      timeOnTarget = 0;
    }
    prevLeft = LeftWheelMotor->position(deg);
  }

  void updateCloseEnoughRot(const double& target)
  {
    if (fabs(rot - target) <= closeEnoughRot || LeftWheelMotor->position(deg) == prevLeft)
    {
      timeOnTarget += timer::system() - prevTime;
    }
    else
    {
      timeOnTarget = 0;
    }
    prevLeft = LeftWheelMotor->position(deg);
  }

  /*
  void goTo(double x, double y)
  {
    // tan^-1(o/a)
    turnTo(atan2((y - yPos), (x - xPos)) * 180 / PI);

    double wantedDistance = pow(pow(x - xPos, 2) + pow(y - yPos, 2), 0.5);
    driveForward(wantedDistance, degrees);
  }
  */
}