#include "odom.h"

#define PI 3.14159265359

static double prevLeft = 0;
static double prevRight = 0;
static double diameter = 2.75;
static double wheeltrack = 1;

namespace team499{

  double xPos = 0;
  double yPos = 0;
  double rotInRadian = 0;

  double xPosWithRot = 0;
  double yPosWithRot = 0;
  double prevRotInRadian = 0;

  void calculateOdom()
  {
    double deltaL = (LeftWheel.AverageRotation() - prevLeft) / 360 * diameter * PI;
    double deltaR = (RightWheel.AverageRotation() - prevRight) / 360 * diameter * PI;
    double deltaA = (deltaR - deltaL) / wheeltrack;
    double deltaS = (deltaR + deltaL) / 2;

    xPos += deltaS * cos(rotInRadian + deltaA / 2);
    yPos += deltaS * sin(rotInRadian + deltaA / 2);

    double rot = iSensor.rotation() * PI / 180;
    xPosWithRot += deltaS * cos(prevRotInRadian + rot / 2);
    yPosWithRot += deltaS * sin(prevRotInRadian + rot / 2);
    prevRotInRadian = rot;

    prevLeft = LeftWheel.AverageRotation();
    prevRight = RightWheel.AverageRotation();
  }

  void odomThreadFunc()
  {
    while(true)
    {
      calculateOdom();
      wait(20,msec);
    }
  }

};