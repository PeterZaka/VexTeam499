/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature SIG_RED = vex::vision::signature (1, 5483, 6795, 6139, -881, 171, -355, 0, 0);
vex::vision::signature SIG_RED_TOP = vex::vision::signature (2, 5477, 9831, 7654, -319, 407, 44, 2.9, 0);
vex::vision::signature SIG_DARKRED_TOP = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision UseThisForVisionSignatures = vex::vision (vex::PORT1, 50, SIG_RED, SIG_RED_TOP, SIG_DARKRED_TOP, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/