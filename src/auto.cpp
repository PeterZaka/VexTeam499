#include "auto.h"

namespace team499 {

  double xPos = 0;
  double yPos = 0;

  int targetTime = 70; // in msec
  int closeEnoughDegrees = 30;
  int closeEnoughDegreesRot = 1;

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

    while (timeOnTarget < targetTime)
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

    double leftEncoder = 0;
    double rightEncoder = 0;
    double prevLeftEncoder = 0;
    double prevRightEncoder = 0;
    double averageEncoder;
    double distanceTraveled;

    double leftMotorError = 0;
    double rightMotorError = 0;

    LeftPID.reset();
    RightPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    while (timeOnTarget < targetTime)
    {
      resetScreen();
      printOnController("encoder", LeftWheelMotor->position(deg));

      // calculate position
      leftEncoder = LeftWheelMotor->position(rev) - prevLeftEncoder;
      rightEncoder = RightWheelMotor->position(rev) - prevRightEncoder;
      averageEncoder = (leftEncoder + rightEncoder) / 2;
      distanceTraveled = averageEncoder / inches * circumference;

      xPos += cos(rot * degreesToRadians) * distanceTraveled;
      yPos += sin(rot * degreesToRadians) * distanceTraveled;

      prevLeftEncoder = LeftWheelMotor->position(rev);
      prevRightEncoder = RightWheelMotor->position(rev);


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
      leftMotorPower = LeftPID.update(LeftWheelMotor->position(deg), amount);
      rightMotorPower = RightPID.update(RightWheelMotor->position(deg), amount);

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower + leftMotorError * rotCorrection, pct);
      RightWheelMotor->spin(fwd, rightMotorPower + rightMotorError * rotCorrection, pct);

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
      printOnController("rot", rot);

      leftMotorPower = LeftTurnPID.update(rot, targetRot);
      rightMotorPower = -RightTurnPID.update(rot, targetRot);

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

  void goTo(double x, double y)
  {
    // tan^-1(o/a)
    turnTo(atan2((y - yPos), (x - xPos)) * 180 / PI);

    double wantedDistance = pow(pow(x - xPos, 2) + pow(y - yPos, 2), 0.5);
    driveForward(wantedDistance, degrees);
  }
}