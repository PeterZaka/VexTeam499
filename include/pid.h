#pragma once

#include "auto.h"

namespace team499{
  
  class PID
  {
    public:

    PID(double Kp, double Ki, double Kd);

    void reset();
    double update(double pos, double target);

    double Kp = 0; // Proportional adjustment to error, error * Kp
    double Ki = 0; // Integral component (adjusts bunch of errors), Integral * Ki
    double Kd = 0; // Derivative component (adjusts difference of error), Derivative * Kd

    private:
      double error;
      double integral;
      double derivative;
      double prevError;
  };

  // PID
  extern PID DrivePID;
  extern PID TurnPID;

}