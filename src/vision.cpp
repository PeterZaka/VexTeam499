#include "vision.h"

vex::vision::signature SIG_RED = vex::vision::signature (1, 5483, 6795, 6139, -881, 171, -355, 2.7, 0);
vex::vision VisionBottom = vex::vision (vex::PORT4, 50, SIG_RED);
vex::vision VisionTop = vex::vision (vex::PORT1, 50, SIG_RED);

bool isGuaranteed = false;

bool detects(vex::vision::signature Signature)
{
  VisionTop.takeSnapshot(Signature);
  if((VisionTop.largestObject.width + VisionTop.largestObject.height > 200) || isGuaranteed)
  {
    return true;
  }
  return false;
}

void waitUntilRed()
{
  while(1)
  {
    VisionBottom.takeSnapshot(SIG_RED);
    if((VisionBottom.largestObject.width + VisionBottom.largestObject.height > 200) || isGuaranteed)
    {
      return;
    }
    wait(20, msec);
  }
}