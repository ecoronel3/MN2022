#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "Parameters.h"

namespace mn
{
    inline bool ReadInputFile(const std::filesystem::path& inputFilePath, InputParams& params)
    {
        if (!std::filesystem::exists(inputFilePath))
        {
            return false;
        }

        std::ifstream file{ inputFilePath };
        if (!file.is_open())
        {
            return false;
        }

        std::string line;
        if (!std::getline(file, line))
        {
            return false;
        }
        std::istringstream iss{ line };
        
        iss >> params.ri >> params.re >> params.m >> params.n >> params.iso >> params.ninst;
        params.m -= 1;

        params.instances.reserve(params.ninst);
        for(int i = 0; i < params.ninst; ++i)
        {
            if (!std::getline(file, line))
            {
                return false;
            }
            std::istringstream values{ line };

            Instance& instance = params.instances.emplace_back();

            
            // temp pared interna
            instance.internalTemps.reserve(params.n);
            for (int j = 0; j < params.n; ++j)
            {
                float& temp = instance.internalTemps.emplace_back();
                values >> temp;
            }

            // temp pared externa
            instance.externalTemps.reserve(params.n);
            for (int j = 0; j < params.n; ++j)
            {
                float& temp = instance.externalTemps.emplace_back();
                values >> temp;
            }
        }

        return true;
    }

    inline bool WriteOutputFile(const std::filesystem::path& outputFilePath, const OutputParams& params)
    {
        // TODO
        return false;
    }
}