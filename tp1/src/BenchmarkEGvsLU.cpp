#include <iostream>
#include <chrono>
#include <filesystem>


#include "FindIsotherm.h"
#include "FileHelper.h"

using Clock = std::chrono::high_resolution_clock;

std::vector<uint64_t> testEG(const mn::InputParams& input, const int count)
{
    std::vector<uint64_t> elapseds;
    elapseds.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        mn::OutputParams output;
        const auto start = Clock::now();
        mn::FindIsothermEG(input, output);
        const auto end = Clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        elapseds.emplace_back(elapsed.count());
    }
    return elapseds;
}

std::vector<uint64_t> testLU(const mn::InputParams& input, const int count)
{
    std::vector<uint64_t> elapseds;
    elapseds.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        mn::OutputParams output;
        const auto start = Clock::now();
        mn::FindIsothermLU(input, output);
        const auto end = Clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        elapseds.emplace_back(elapsed.count());
    }
    return elapseds;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Cantidad de parametros invalida. Se esperaban 2 parametros.\n";
        return -1;
    }

    std::filesystem::path inputFile = argv[1];
    int count = std::atoi(argv[2]);

    count = std::max(10, count);

    mn::InputParams input;
    if (mn::ReadInputFile(inputFile, input))
    {
        std::cout << "{\n";
        std::cout << "\"n\": \"" << input.n << "\",\n";
        std::cout << "\"m\": \"" << input.m << "\",\n";
        std::cout << "\"ninst\": \"" << input.ninst << "\",\n";
        std::cout << "\"EG\": [";
        const auto egTimes = testEG(input, count);
        for(std::size_t i = 0; i < egTimes.size(); ++i)
        {
            std::cout << "\"" << egTimes[i] << "\"";
            if (i < egTimes.size() - 1)
            {
                 std::cout << ", ";
            }
        }
        std::cout << "],\n";

        std::cout << "\"LU\": [";
        const auto luTimes = testLU(input, count);
        for(std::size_t i = 0; i < luTimes.size(); ++i)
        {
            std::cout << "\"" << luTimes[i] << "\"";
            if (i < luTimes.size() - 1)
            {
                 std::cout << ", ";
            }
        }
        std::cout << "]\n";
        std::cout << "}\n";
    }
    return 0;
}