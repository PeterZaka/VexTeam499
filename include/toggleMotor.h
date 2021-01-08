#pragma once

#include "vex.h"
#include "motorGroup.h"

namespace team499 {

	class toggleMotor : public motorGroup
	{

		friend class controllerInput;

	public:

		// CONSTRUCTORS
		toggleMotor(std::string name, double defaultPower, std::vector<vex::motor*> const& motors);
		toggleMotor(std::string name, double (*powerFunction)(), std::vector<vex::motor*> const& motors);

		void Update() override;


	private:

		// toggles during update cycle
		bool m_isToggled = false;

		bool m_anyButtonWasTrue = false;

	};
}