#include "pid.h"

namespace team499{

  PID::PID(double Kp, double Ki, double Kd) : Kp(Kp), Ki(Ki), Kd(Kd) {}

  void PID::reset()
  {
    integral = 0;
    prevError = 0;
  }

  double PID::update(double pos, double target, bool under)
  {
    error = target - pos;
    integral += error;
    integral = clamp(integral, -100000, 100000);
    if((pos > target && under) || (pos < target && !under))
    {
      integral = 0;
    }
    if (fabs(leftMotorPower) > maxPower - 10)
    {
      integral = 0;
    }
    derivative = error - prevError;
    prevError = error;

    double PIDvalue = (error * Kp) + (integral * Ki) + (derivative * Kd);
    return clamp(PIDvalue, -maxPower, maxPower);
  }
}