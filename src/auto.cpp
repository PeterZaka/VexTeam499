#include "auto.h"

namespace team499 {

  double maxPower = 100;

  int targetTime = 70; // in msec
  double closeEnoughDeg = 50;
  double closeEnoughRot = 3;

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
      LeftWheel.SpinMotorsAt(leftMotorPower + leftMotorError);
      RightWheel.SpinMotorsAt(rightMotorPower + rightMotorError);

      wait(20, msec);
    }
    targetThread.interrupt();

    LeftWheel.Stop();
    RightWheel.Stop();
  }

  void turnTo(double amount)
  {
    resetAuto();

    targetRot = quickestRotation(rot, amount);
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
      LeftWheel.SpinMotorsAt(leftMotorPower);
      RightWheel.SpinMotorsAt(rightMotorPower);

      wait(20, msec);
    }
    targetThread.interrupt();

    LeftWheel.Stop();
    RightWheel.Stop();
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
      else if(fabs(LeftWheelMotor->velocity(pct)) <= 1 && fabs(averageEncoder) > closeEnoughDeg)
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
      else if(fabs(LeftWheelMotor->velocity(pct)) <= 1 && fabs(rot - startingRot) > closeEnoughRot)
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
    //targetRot = rot;

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
    if (rot > targetRot) // rotated to the right
    {
      leftMotorError = -fabs(rot - targetRot);
      rightMotorError = fabs(rot - targetRot);
    }
    else if (rot < targetRot) // rotated to the left
    {
      leftMotorError = fabs(rot - targetRot);
      rightMotorError = -fabs(rot - targetRot);
    }
    else
    {
      leftMotorError = 0;
      rightMotorError = 0;
    }

    leftMotorError = clamp(leftMotorError * rotCorrection, -30, 30) * clamp(fabs(leftMotorPower) / 100, 0, 1);
    rightMotorError = clamp(rightMotorError * rotCorrection, -30, 30) * clamp(fabs(rightMotorPower) / 100, 0, 1);
  }
}