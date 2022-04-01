#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace metnum
{

    struct Instance
    {
        std::vector<float> internalTemps;
        std::vector<float> externalTemps;
    };

    struct InputParams
    {
        int ri{0};
        int re{0};
        int m{0};
        int n{0};
        int iso{0};
        int ninst{0};
        std::vector<Instance> instances;
    };

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
            iss.str(line);

            Instance& instance = params.instances.emplace_back();

            
            // temp pared interna
            instance.internalTemps.reserve(params.n);
            for (int j = 0; j < params.n; ++j)
            {
                float& temp = instance.internalTemps.emplace_back();
                iss >> temp;
            }

            // temp pared externa
            instance.externalTemps.reserve(params.n);
            for (int j = 0; j < params.n; ++j)
            {
                float& temp = instance.externalTemps.emplace_back();
                iss >> temp;
            }
        }


        return false;
    }

    inline bool WriteOutputFile(const std::filesystem::path& outputFilePath)
    {
        // TODO
        return false;
    }


}