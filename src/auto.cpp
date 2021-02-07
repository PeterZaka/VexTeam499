#include "auto.h"

namespace team499 {

  double maxPower = 100;

  int targetTime = 100; // in msec
  double closeEnoughDeg = 30;
  double closeEnoughRot = 2;

  int timeOnTarget = 0;
  int prevTime = 0;
  double prevEncoder;
  double averageEncoder;
  double leftMotorError;
  double rightMotorError;
  double targetRot;

  void colHit(vex::axisType a, double b, double c, double d)
  {
    timeOnTarget = targetTime;
  }

  void driveForward()
  {
    resetAuto();

    while(timeOnTarget < targetTime)
    {
      correctRobot();

      LeftWheelMotor->spin(fwd,
      maxPower + (leftMotorError * rotCorrection * (fabs(LeftWheelMotor->power()) / maxPower)),
      pct);
      RightWheelMotor->spin(fwd,
      maxPower + (leftMotorError * rotCorrection * (fabs(RightWheelMotor->power()) / maxPower)),
      pct);

      averageEncoder = (LeftWheelMotor->position(deg) + RightWheelMotor->position(deg)) / 2;

      // check if close stopped or collided
      if (fabs(averageEncoder - prevEncoder) <= 0.1)
      {
        timeOnTarget += 5;
      }
      else
      {
        timeOnTarget = 0;
      }
      iSensor.collision(colHit);

      prevEncoder = averageEncoder;
      prevTime = timer::system();
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void driveForward(double amount, unit units)
  {
    amount *= units;

    resetAuto();

    double leftMotorPower;
    double rightMotorPower;

    while (timeOnTarget < targetTime)
    {
      //resetScreen();
      //printOnController("encoder", LeftWheelMotor->position(deg));

      correctRobot();

      // calculate PID
      leftMotorPower = DrivePID.update(LeftWheelMotor->position(deg), amount);
      rightMotorPower = leftMotorPower;

      // update wheel power
      LeftWheelMotor->spin(fwd,
      leftMotorPower + (leftMotorError * rotCorrection * (fabs(LeftWheelMotor->power()) / maxPower)),
      pct);
      RightWheelMotor->spin(fwd,
      rightMotorPower + (leftMotorError * rotCorrection * (fabs(RightWheelMotor->power()) / maxPower)),
      pct);

      // check if close enough to target
      averageEncoder = (LeftWheelMotor->position(deg) + RightWheelMotor->position(deg)) / 2;
      updateCloseEnoughDeg(amount);

      prevEncoder = averageEncoder;
      prevTime = timer::system();
      wait(20, msec);
    }
    LeftWheelMotor->spin(fwd, 0, pct);
    RightWheelMotor->spin(fwd, 0, pct);
  }

  void turnTo(double targetRot)
  {
    resetAuto();

    targetRot = quickestRotation(rot, targetRot);

    double leftMotorPower;
    double rightMotorPower;

    while (timeOnTarget < targetTime)
    {
      //resetScreen();
      //printOnController("rot", rot);

      // calculate PID
      leftMotorPower = TurnPID.update(rot, targetRot);
      rightMotorPower = -leftMotorPower;

      // update wheel power
      LeftWheelMotor->spin(fwd, leftMotorPower, pct);
      RightWheelMotor->spin(fwd, rightMotorPower, pct);

      // check if close enough to target
      // average is left only because average of both will always be 0
      averageEncoder = LeftWheelMotor->position(deg);
      updateCloseEnoughRot(targetRot);

      prevEncoder = averageEncoder;
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
    if (fabs(averageEncoder - target) <= closeEnoughDeg)
    {
      timeOnTarget += timer::system() - prevTime;
    }
    else if(fabs(averageEncoder - prevEncoder) <= 0.1)
    {
      timeOnTarget += 5;
    }
    else
    {
      timeOnTarget = 0;
    }
  }

  void updateCloseEnoughRot(const double& target)
  {
    if (fabs(rot - target) <= closeEnoughRot)
    {
      timeOnTarget += timer::system() - prevTime;
    }
    else if(fabs(averageEncoder - prevEncoder) <= 0.1)
    {
      timeOnTarget += 5;
    }
    else
    {
      timeOnTarget = 0;
    }
  }

  void resetAuto()
  {
    timeOnTarget = 0;
    averageEncoder = 0;
    targetRot = rot;

    leftMotorError = 0;
    rightMotorError = 0;

    DrivePID.reset();
    TurnPID.reset();

    LeftWheelMotor->resetPosition();
    RightWheelMotor->resetPosition();

    prevTime = timer::system();
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