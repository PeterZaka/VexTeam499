#include "motors.h"

team499::motorGroup LeftWheel("LeftWheel", []() {return round(Controller1.Axis3.position()); }, { &backDriveLeft, &topDriveLeft });
team499::motorGroup RightWheel("RightWheel", []() {return round(Controller1.Axis2.position()); }, { &backDriveRight, & topDriveRight });
team499::motorGroup Intakes("Intakes", 100, { &intake });
team499::toggleMotor FlyWheel("FlyWheel", &team499::GetGearShiftPower, { &flywheel });
team499::motorGroup SideRollers("SideRollers", 100, { &sideRollerLeft,&sideRollerRight });