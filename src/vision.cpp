#include "vision.h"

vex::vision::signature SIG_RED = vex::vision::signature (1, 5483, 6795, 6139, -881, 171, -355, 2.7, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision1 = vex::vision (vex::PORT4, 50, SIG_RED, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);

bool isGuaranteed = false;

void waitUntilRed()
{
  while(1)
  {
    Vision1.takeSnapshot(SIG_RED);
    if((Vision1.largestObject.width + Vision1.largestObject.height > 200) || isGuaranteed)
    {
      return;
    }
    wait(20, msec);
  }
}