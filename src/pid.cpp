#include "pid.h"

namespace team499{

  PID::PID(double Kp, double Ki, double Kd) : Kp(Kp * 20), Ki(Ki * 20), Kd(Kd * 20) {}

  void PID::reset()
  {
    integral = 0;
    prevError = 0;
  }

  double PID::update(double pos, double target)
  {
    error = (target - pos) / (timer::system() - prevTime);
    integral += error;
    if (pos > target || fabs(error) > 200)
    {
      integral = 0;
    }
    derivative = error - prevError;
    prevError = error;

    double PIDvalue = (error * Kp) + (integral * Ki) + (derivative * Kd);
    return clamp(PIDvalue, -maxPower, maxPower);
  }
}