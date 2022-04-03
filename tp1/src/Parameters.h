#pragma once

#include <vector>

namespace mn
{
    struct Instance
    {
        std::vector<float> internalTemps;
        std::vector<float> externalTemps;
    };

    struct InputParams
    {
        float ri{ 0.0f };
        float re{ 0.0f };
        int m{ 0 };
        int n{ 0 };
        int iso{ 0 };
        int ninst{ 0 };
        std::vector<Instance> instances;
    };

    struct OutputParams
    {
        // TODO
    };
}