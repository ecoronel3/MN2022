#include <iostream>
#include <chrono>
#include <filesystem>


#include "FindIsotherm.h"
#include "FileHelper.h"

using Clock = std::chrono::high_resolution_clock;

double testEG(const mn::InputParams& input, const int count)
{
    double acum{0.0};
    for (int i = 0; i < count; ++i)
    {
        mn::OutputParams output;
        const auto start = Clock::now();
        mn::FindIsothermEG(input, output);
        const auto end = Clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        acum += static_cast<double>(elapsed.count());
    }

    return acum / count;
}

double testLU(const mn::InputParams& input, const int count)
{
    double acum{0.0};
    for (int i = 0; i < count; ++i)
    {
        mn::OutputParams output;
        const auto start = Clock::now();
        mn::FindIsothermLU(input, output);
        const auto end = Clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        acum += static_cast<double>(elapsed.count());
    }

    return acum / count;
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
        std::cout << testEG(input, count);
        std::cout << ' ';
        std::cout << testLU(input, count);
        std::cout << '\n';
    }
    return 0;
}