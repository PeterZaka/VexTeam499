#include "drivehelp.h"

namespace team499{

  double straightRot = 0;
  bool isDrivingStraight = false;

  double turnDirection = 0;
  bool isTurning = false;

  void driveStraight(motorGroup* left, motorGroup* right)
  {
    if(!isCalibrated || left->m_currentPower == 0)
    {
      return;
    }

    double leftMotorError = 0;
    double rightMotorError = 0;

    if(fabs(left->m_currentPower - right->m_currentPower) < 5)
    {
      if(!isDrivingStraight)
      {
        isDrivingStraight = true;
        straightRot = rot;
      }

      // adjust to go straight
      if (rot - 0.2 > straightRot) // rotated to the right
      {
        leftMotorError = straightRot - rot;
        rightMotorError = rot - straightRot;
      }
      else if (rot + 0.2 < straightRot) // rotated to the left
      {
        leftMotorError = rot - straightRot;
        rightMotorError = straightRot - rot;
      }

      left->SpinMotorsAt(left->m_currentPower + leftMotorError);
      right->SpinMotorsAt(right->m_currentPower + rightMotorError);
    }
    else
    {
      isDrivingStraight = false;
    }
  }

  void turnToButton()
  {
    if(!isCalibrated)
    {
      return;
    }

    // if no buttons are pressed
    if(!(Controller1.ButtonUp.pressing() || Controller1.ButtonRight.pressing() || Controller1.ButtonDown.pressing() || Controller1.ButtonLeft.pressing()))
    {
      isTurning = false;
      return;
    }
    
    if(!isTurning)
    {
      isTurning = true;
      LeftTurnPID.reset();
      RightTurnPID.reset();
    }

    if(Controller1.ButtonUp.pressing() && Controller1.ButtonLeft.pressing())
    {
      turnDirection = 315;
    }
    else if(Controller1.ButtonUp.pressing() && Controller1.ButtonRight.pressing())
    {
      turnDirection = 45;
    }
    else if(Controller1.ButtonDown.pressing() && Controller1.ButtonLeft.pressing())
    {
      turnDirection = 225;
    }
    else if(Controller1.ButtonDown.pressing() && Controller1.ButtonRight.pressing())
    {
      turnDirection = 135;
    }
    else if(Controller1.ButtonUp.pressing())
    {
      turnDirection = 0;
    }
    else if(Controller1.ButtonRight.pressing())
    {
      turnDirection = 90;
    }
    else if(Controller1.ButtonDown.pressing())
    {
      turnDirection = 180;
    }
    else if(Controller1.ButtonLeft.pressing())
    {
      turnDirection = 270;
    }

    turnDirection = quickestRotation(rot, turnDirection);

    double leftMotorPower = LeftTurnPID.update(rot, turnDirection);
    double rightMotorPower = -RightTurnPID.update(rot , turnDirection);

    // update wheel power
    LeftWheelMotor->spin(fwd, leftMotorPower, pct);
    RightWheelMotor->spin(fwd, rightMotorPower, pct);
  }
}