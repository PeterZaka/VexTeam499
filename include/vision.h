#pragma once

#include "vex.h"

extern vex::vision::signature SIG_RED;
extern vex::vision::signature SIG_RED_TOP;
extern vex::vision VisionBottom;
extern vex::vision VisionTop;

extern bool isGuaranteed;

bool detects(vex::vision::signature Signature);

void waitUntilRed();