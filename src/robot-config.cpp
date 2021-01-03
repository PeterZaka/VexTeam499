#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// Motors
motor driveLeft = motor(PORT1, ratio18_1, false);
motor driveRight = motor(PORT2, ratio18_1, true);
motor intakeLeft = motor(PORT5, ratio18_1, true);
motor intakeRight = motor(PORT6, ratio18_1, false);
motor flywheelLeft = motor(PORT10, ratio6_1, false);
motor flywheelRight = motor(PORT13, ratio6_1, true);
motor sideRollerLeft = motor(PORT11, ratio18_1, false);
motor sideRollerRight = motor(PORT12, ratio18_1, true);

// Controllers
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

/*
motor driveLeft = motor(PORT1, ratio18_1, false);
motor driveRight = motor(PORT2, ratio18_1, true);
motor intakeLeft = motor(PORT5, ratio18_1, true);
motor intakeRight = motor(PORT6, ratio18_1, false);
motor flywheelLeft = motor(PORT10, ratio6_1, false);
motor flywheelRight = motor(PORT13, ratio6_1, true);
motor sideRollerLeft = motor(PORT11, ratio18_1, false);
motor sideRollerRight = motor(PORT12, ratio18_1, true);
*/

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}