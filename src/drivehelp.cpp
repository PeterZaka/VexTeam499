#include "drivehelp.h"

namespace team499{

  double straightRot = 0;
  bool isDrivingStraight = false;

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

}