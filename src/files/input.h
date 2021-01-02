#pragma once

#include "vex.h"

extern double gearShiftPower;
extern bool changedGearShift;

double round(double number);

double GetGearShiftPower();

void updateGearShift();

void printGearShift();

void printThis(float thing);
