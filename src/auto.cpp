#include "auto.h"

namespace team499{

  void driveForwardPID(double amount, unit units)
  {
    amount *= units;
  }

  void driveForwardInertial(double amount, unit units)
  {
    amount *= units;

    double targetRot = rot;
    double timeOnTarget = 0;
    double leftMotorPower;
    double rightMotorPower;

    LeftWheelMotor.resetPosition();
    RightWheelMotor.resetPosition();

    while(timeOnTarget < targetTime)
    {
      // slow down on approach / back up when too far
      leftMotorPower = std::max(-maxPower , std::min( ( LeftWheelMotor.position(deg) - amount ) * slowDown, maxPower ) );
      rightMotorPower = std::max(-maxPower , std::min( ( RightWheelMotor.position(deg) - amount ) * slowDown, maxPower ) );

      // adjust to go straight
      if(rot - 0.5 > targetRot) // rotated to the right
      {
        leftMotorPower -= rot - targetRot;
        rightMotorPower += rot - targetRot;
      }
      else if (rot + 0.5 < targetRot) // rotated to the left
      {
        leftMotorPower -= rot - targetRot;
        rightMotorPower += rot - targetRot;
      }

      // update wheel power
      LeftWheelMotor.spin(fwd, leftMotorPower, pct);
      RightWheelMotor.spin(fwd, rightMotorPower, pct);

      // check if close enough for long enough
      if(std::abs(LeftWheelMotor.position(deg) - amount) < closeEnoughDegrees)
      {
        timeOnTarget += 20;
      }
      else
      {
        timeOnTarget = 0;
      }
      wait(20, msec);
    }
    LeftWheelMotor.spin(fwd, 0, pct);
    RightWheelMotor.spin(fwd, 0, pct);
  }

  void driveRightInertial(double targetRot)
  {
    double timeOnTarget = 0;
    double leftMotorPower;
    double rightMotorPower;

    LeftWheelMotor.resetPosition();
    RightWheelMotor.resetPosition();

    while(timeOnTarget < targetTime)
    {
      // slow down on approach / back up when too far
      leftMotorPower = std::max(-maxPower , std::min( ( targetRot - rot ) * slowDownRot, maxPower ) );
      rightMotorPower = std::max(-maxPower , std::min( ( rot - targetRot ) * slowDownRot, maxPower ) );

      // update wheel power
      LeftWheelMotor.spin(fwd, leftMotorPower, pct);
      RightWheelMotor.spin(fwd, rightMotorPower, pct);

      // check if close enough for long enough
      if(std::abs(rot - targetRot) < closeEnoughDegreesRot)
      {
        timeOnTarget += 20;
      }
      else
      {
        timeOnTarget = 0;
      }
      wait(20, msec);
    }
    LeftWheelMotor.spin(fwd, 0, pct);
    RightWheelMotor.spin(fwd, 0, pct);
  }

}