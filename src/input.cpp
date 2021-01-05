#include "input.h"

namespace team499 {

    input::input(
        bool(*inputFunc)(),
        const std::vector<motorGroup*>& positiveGroups,
        const std::vector<motorGroup*>& negativeGroups)
        :
        inputFunc(inputFunc),
        positiveGroups(positiveGroups),
        negativeGroups(negativeGroups)
    {}

    void input::Update()
    {
        //printf("%d\n",input());
        if (inputFunc())
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