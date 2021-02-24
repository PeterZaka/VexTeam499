#include "drivehelp.h"

namespace team499{

  double straightRot = 0;
  bool isDrivingStraight = false;

  double turnDirection = 0;
  bool isTurning = false;

  void driveStraight(motorGroup* left, motorGroup* right)
  {
    if(!isCalibrated || left->m_currentPower < 40)
    {
      return;
    }

    double leftMotorError = 0;
    double rightMotorError = 0;

    if(fabs(left->m_currentPower - right->m_currentPower) < 5)
    {
      // resetScreen();
      // printOnController("Driving straight");
      if(!isDrivingStraight)
      {
        isDrivingStraight = true;
        straightRot = rot;
      }

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

      left->SpinMotorsAt(left->m_currentPower + (clamp(leftMotorError * rotCorrection, -30, 30) * clamp(fabs(left->m_currentPower) / 100, 0, 1)));
      right->SpinMotorsAt(left->m_currentPower + (clamp(rightMotorError * rotCorrection, -30, 30) * clamp(fabs(left->m_currentPower) / 100, 0, 1)));
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
      resetAuto();
      TurnPID.reset();
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

    leftMotorPower = TurnPID.update(rot, turnDirection);
    rightMotorPower = -leftMotorPower;

    // update wheel power
    LeftWheelMotor->spin(fwd, leftMotorPower, pct);
    RightWheelMotor->spin(fwd, rightMotorPower, pct);
  }
}