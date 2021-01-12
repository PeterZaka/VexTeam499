#include "motors.h"

team499::motorGroup LeftWheel("LeftWheel", []() {return round(Controller1.Axis3.position()); }, { &driveLeft });
team499::motorGroup RightWheel("RightWheel", []() {return round(Controller1.Axis2.position() * 0.9); }, { &driveRight });
team499::motorGroup Intakes("Intakes", 127, { &intakeLeft,&intakeRight });
team499::toggleMotor FlyWheel("FlyWheel", &team499::GetGearShiftPower, { &flywheelLeft,&flywheelRight });
team499::motorGroup SideRollers("SideRollers", 127, { &sideRollerLeft,&sideRollerRight });