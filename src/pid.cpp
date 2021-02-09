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
    integral = clamp(integral, -100000, 100000);
    if (fabs(pos) > fabs(target) || fabs(leftMotorPower) > maxPower - 10)
    {
      integral = 0;
    }
    derivative = error - prevError;
    prevError = error;

    //printf("\npos: %.2lf tar: %.2lf\n", pos, target);
    //printf("error: %.2lf\n", (error * Kp));
    //printf("int: %.2lf\n", (integral* Ki));
    //printf("der: %.2lf\n", (derivative * Kd));

    double PIDvalue = (error * Kp) + (integral * Ki) + (derivative * Kd);

    //printf("pid: %.2lf\n", PIDvalue);
    
    return clamp(PIDvalue, -maxPower, maxPower);
  }
}