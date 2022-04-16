#pragma once

#include <vector>

#include "VectorN.h"
#include "FPType.h"

namespace mn
{
    struct Instance
    {
        std::vector<FPType> internalTemps;
        std::vector<FPType> externalTemps;
    };

    struct InputParams
    {
        FPType ri{ 0.0 };
        FPType re{ 0.0 };
        int m{ 0 };
        int n{ 0 };
        FPType iso{ 0.0 };
        int ninst{ 0 };
        std::vector<Instance> instances;
    };

    struct OutputTemps 
    {
        std::vector<FPType> internal;
        VectorN<FPType> inner;
        std::vector<FPType> external;
    };

    struct OutputParams
    {
        std::vector<OutputTemps> temps;
    };
}
