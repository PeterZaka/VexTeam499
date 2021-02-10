#include "auto.h"

namespace team499 {

  double maxPower = 100;

  int targetTime = 100; // in msec
  double closeEnoughDeg = 30;
  double closeEnoughRot = 2;

  int timeOnTarget = 0;
  double target;
  double leftMotorError;
  double rightMotorError;
  double targetRot;

  double leftMotorPower = 0;
  double rightMotorPower = 0;

  void colHit(vex::axisType a, double b, double c, double d)
  {
    timeOnTarget = targetTime;
  }

  void driveForward(double amount, unit units)
  {
    resetAuto();

    double under = true;
    if(amount < 0)
    {
      under = false;
    }

    amount *= units;
    target = amount;
    vex::thread targetThread(updateCloseEnoughDeg);

    while (timeOnTarget < targetTime)
    {
      correctRobot();

      // calculate PID
      leftMotorPower = DrivePID.update(LeftWheelMotor->position(deg), amount, under);
      rightMotorPower = leftMotorPower;

      // update wheel power
      LeftWheelMotor->spin(fwd,
      leftMotorPower + leftMotorError,
      pct);
      RightWheelMotor->spin(fwd,
      rightMotorPower + rightMotorError,
      pct);

      wait(20, msec);
    }
    targetThread.interrupt();

    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void turnTo(double targetRot)
  {
    resetAuto();

    targetRot = quickestRotation(rot, targetRot);
    target = targetRot;
    vex::thread targetThread(updateCloseEnoughRot);

    double under = true;
    if(rot > targetRot)
    {
      under = false;
    }

    while (timeOnTarget < targetTime)
    {
      // calculate PID
      leftMotorPower = TurnPID.update(rot, targetRot, under);
      rightMotorPower = -leftMotorPower;

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, rightMotorPower, pct);

      wait(20, msec);
    }
    targetThread.interrupt();

    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void resetCloseEnoughs()
  {
    targetTime = defaultTargetTime;
    closeEnoughDeg = defaultCloseEnoughDeg;
    closeEnoughRot = defaultCloseEnoughRot;
  }

  void updateCloseEnoughDeg()
  {
    int prevTime = timer::system();
    double averageEncoder;
    while(timeOnTarget < targetTime)
    {
      averageEncoder = (LeftWheelMotor->position(deg) + RightWheelMotor->position(deg)) / 2;
      // check if on target
      if (fabs(averageEncoder - target) <= closeEnoughDeg)
      {
        timeOnTarget += timer::system() - prevTime;
      }
      // check if stopped
      else if(fabs(LeftWheelMotor->power()) <= 1 && fabs(averageEncoder) > 30)
      {
        timeOnTarget += timer::system() - prevTime;
      }
      else
      {
        timeOnTarget = 0;
      }
      prevTime = timer::system();
      wait(5, msec);
    }
  }

  void updateCloseEnoughRot()
  {
    int prevTime = timer::system();
    double startingRot = rot;
    while(timeOnTarget < targetTime)
    {
      // check if on target
      if (fabs(rot - target) <= closeEnoughRot)
      {
        timeOnTarget += timer::system() - prevTime;
      }
      // check if stopped
      else if(fabs(LeftWheelMotor->power()) <= 1 && fabs(rot - startingRot) > 0.5)
      {
        timeOnTarget += timer::system() - prevTime;
      }
      else
      {
        timeOnTarget = 0;
      }
      prevTime = timer::system();
      wait(5, msec);
    }
  }

  void resetAuto()
  {
    timeOnTarget = 0;
    targetRot = rot;

    leftMotorError = 0;
    rightMotorError = 0;

    leftMotorPower = 0;
    rightMotorPower = 0;

    DrivePID.reset();
    TurnPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();
  }

  void correctRobot()
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
    leftMotorError *= rotCorrection * (fabs(LeftWheelMotor->power()) / 100);
    rightMotorError *= rotCorrection * (fabs(RightWheelMotor->power()) / 100);
  }
}