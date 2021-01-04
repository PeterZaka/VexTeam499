#include "controllerInput.h"

namespace team499 {

    controllerInput::controllerInput(
        bool(*inputFunc)(),
        const std::vector<motorGroup*>& positiveGroups,
        const std::vector<motorGroup*>& negativeGroups)
        :
        input(inputFunc),
        positiveGroups(positiveGroups),
        negativeGroups(negativeGroups)
    {}

    void controllerInput::updateButton()
    {
        //printf("%d\n",input());
        if (input())
        {
            for (auto mg : positiveGroups)
            {
                mg->PositiveActivate();
            }
            for (auto mg : negativeGroups)
            {
                mg->NegativeActivate();
            }
        }
    }
}