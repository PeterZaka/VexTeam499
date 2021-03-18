#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// Motors
motor backDriveLeft = motor(PORT1, ratio18_1, false);
motor backDriveRight = motor(PORT2, ratio18_1, true);
motor topDriveLeft = motor(PORT3, ratio18_1, false);
motor topDriveRight = motor(PORT9, ratio18_1, true);
motor intake = motor(PORT6, ratio18_1, false);
motor flywheel = motor(PORT10, ratio6_1, false); // or port 13
motor sideRollerLeft = motor(PORT11, ratio18_1, false);
motor sideRollerRight = motor(PORT14, ratio18_1, true);

// Sensors
inertial iSensor = inertial(PORT8);

// Controllers
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

bumper Bumper = bumper(Brain.ThreeWirePort.H);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}