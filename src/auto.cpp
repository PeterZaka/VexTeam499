#include "auto.h"

namespace team499 {

  void driveForwardPID(double amount, unit units)
  {
    amount *= units;

    int timeOnTarget = 0;
    double leftMotorPower = 50;
    double rightMotorPower = 50;

    LeftPID.reset();
    RightPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    while(timeOnTarget < targetTime)
    {
      leftMotorPower = LeftPID.update(LeftWheelMotor->position(deg), amount);
      rightMotorPower = RightPID.update(LeftWheelMotor->position(deg), amount);

      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, leftMotorPower, pct);

      // check if close enough for long enough
      if (std::abs(LeftWheelMotor->position(deg) - amount) < closeEnoughDegrees)
      {
        timeOnTarget += 20;
      }
      else
      {
        timeOnTarget = 0;
      }
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void driveForward(double amount, unit units)
  {
    amount *= units;

    double targetRot = rot;
    double timeOnTarget = 0;
    double leftMotorPower = 50;
    double rightMotorPower = 50;

    double leftMotorError = 0;
    double rightMotorError = 0;

    LeftPID.reset();
    RightPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    while (timeOnTarget < targetTime)
    {
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

      // PID
      leftMotorPower = LeftPID.update(LeftWheelMotor->position(deg), amount, leftMotorError);
      rightMotorPower = RightPID.update(RightWheelMotor->position(deg), amount, rightMotorError);

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, rightMotorPower, pct);

      // check if close enough for long enough
      if (std::abs(LeftWheelMotor->position(deg) - amount) < closeEnoughDegrees)
      {
        timeOnTarget += 20;
      }
      else
      {
        timeOnTarget = 0;
      }
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void turnTo(double targetRot)
  {
    targetRot = quickestRotation(rot, targetRot);

    double timeOnTarget = 0;
    double leftMotorPower;
    double rightMotorPower;

    LeftTurnPID.reset();
    RightTurnPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    while (timeOnTarget < targetTime)
    {
      resetScreen();
      printOnController("Rotation", rot);

      leftMotorPower = LeftTurnPID.update(rot, targetRot);
      rightMotorPower = -RightTurnPID.update(rot , targetRot);

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, rightMotorPower, pct);

      // check if close enough for long enough
      if (std::abs(rot - targetRot) < closeEnoughDegreesRot)
      {
        timeOnTarget += 20;
      }
      else
      {
        timeOnTarget = 0;
      }
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }
}