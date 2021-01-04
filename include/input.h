#pragma once

#include "vex.h"

namespace team499 {

	extern double gearShiftPower;
	extern bool changedGearShift;

	double roundToDigit(double number);

	double GetGearShiftPower();

	void updateGearShift();

	void printGearShift();

	void printThis(float thing);

}