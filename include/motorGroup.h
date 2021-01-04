#pragma once

#include <vector>
#include "string.h"
#include "input.h"
#include "vex.h"

namespace team499 {

    class motorGroup
    {

        friend class controllerInput;

    public:

        // CONSTRUCTORS

        // motorGroup groups together motors to allow easier control
        // defaultPower - power of the motorGroup that changes from 0 to a number that doesn't change
        // powerFunction - power of the motorGroup that changes from 0 to a number that does change
        motorGroup(std::string name, double defaultPower, const std::vector<vex::motor*>& motors);
        motorGroup(std::string name, double (*powerFunction)(), const std::vector<vex::motor*>& motors);

        // HELPER FUNCTIONS
        float AverageRotation() const;
        void ResetEncoders();

        // AUTONOMOUS FUNCTIONS
        void SpinMotorsTo(double pow, double degrees);
        void CorrectMotors(double degrees);
        void WaitUntilReaches(float degrees);

        // USERCONTROL FUNCTIONS
        void SpinMotorsAt(double const motorGroupPower) const;

        // MISC
        void PrintRotation();

        // Updates motor (Use at UpdateAllMotors at end of cycle instead)
        virtual void Update()
        {
            this->UpdateDefaultPower();
            SpinMotorsAt(m_currentPower * m_anyButtonPressed);
            m_anyButtonPressed = false;
        }


    protected:

        // true if button pressed during cycle
        bool m_anyButtonPressed;

        double m_currentPower;


    private:

        // called when in positive group and button pressed
        void PositiveActivate();

        // called when in negative group and button pressed
        void NegativeActivate();

        // checks if has a power function and applies it
        void UpdateDefaultPower();


        // name of motor group
        std::string m_name;

        // determines power with constant value
        const double m_defaultPower;

        // determines power with changing value
        double (*m_powerFunction)();

        // motors in the motor group
        std::vector<vex::motor*> m_motors;
    };

    // Usercontrol - Calls update for all motor groups
    void UpdateAllMotors();
    
    // Usercontrol (optional) - Used to record usercontrol
    void PrintWantedMotors();
    
    // Misc - Reset all motor rotations from all groups
    void ResetAllMotorRotations();

    extern std::vector<motorGroup*> allMotorGroups;

}