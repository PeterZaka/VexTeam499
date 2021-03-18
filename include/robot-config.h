using namespace vex;

extern brain Brain;

extern motor backDriveLeft;
extern motor backDriveRight;
extern motor topDriveLeft;
extern motor topDriveRight;
extern motor intake;
extern motor flywheel;
extern motor sideRollerLeft;
extern motor sideRollerRight;

extern inertial iSensor;

extern controller Controller1;
extern controller Controller2;

extern bumper Bumper;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
