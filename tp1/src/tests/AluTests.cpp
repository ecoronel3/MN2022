#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <filesystem>

#include "FindIsotherm.h"
#include "FileHelper.h"

namespace
{
    std::vector<double> ReadExpectedFile(std::filesystem::path expectedFilename)
    {
        std::vector<double> res;
        std::ifstream file{ expectedFilename };
        if (!file.is_open())
        {
            return res;
        }

        std::string line;
        while (std::getline(file, line))
        {
            const double value = std::stod(line);
            res.emplace_back(value);
        }
        return res;
    }

    std::vector<double> Copy(const mn::OutputParams& output)
    {
        std::vector<double> res;
        std::size_t size{0};

        for(const auto& temps: output.temps)
        {
            size += temps.internal.size() + temps.inner.size() + temps.external.size();
        }

        res.reserve(size);
        
        for(const auto& temps: output.temps)
        {
            std::copy(temps.internal.begin(), temps.internal.end(), std::back_inserter(res) );
            for(int i = 0; i < temps.inner.size(); ++i )
            {
                res.emplace_back(temps.inner(i));
            }
            std::copy(temps.external.begin(), temps.external.end(), std::back_inserter(res) );
        }
        return res;
    }

}

TEST(AluTests, Test1)
{
    std::vector<double> expected = ReadExpectedFile("tests_alu/test1.expected");
    mn::InputParams input;
    mn::ReadInputFile("tests_alu/test1.in", input);

    mn::OutputParams output;

    mn::FindIsotherm(1, input, output);
    std::vector<double> results = Copy(output);

    EXPECT_EQ(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected[i], results[i]);
    }
}

TEST(AluTests, Test2)
{
    std::vector<double> expected = ReadExpectedFile("tests_alu/test2.expected");
    mn::InputParams input;
    mn::ReadInputFile("tests_alu/test2.in", input);

    mn::OutputParams output;

    mn::FindIsotherm(1, input, output);
    std::vector<double> results = Copy(output);

    EXPECT_EQ(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected[i], results[i]);
    }
}

TEST(AluTests, Test3)
{
    std::vector<double> expected = ReadExpectedFile("tests_alu/test3.expected");
    mn::InputParams input;
    mn::ReadInputFile("tests_alu/test3.in", input);

    mn::OutputParams output;

    mn::FindIsotherm(1, input, output);
    std::vector<double> results = Copy(output);

    EXPECT_EQ(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected[i], results[i]);
    }
}

TEST(AluTests, Test4)
{
    std::vector<double> expected = ReadExpectedFile("tests_alu/test4.expected");
    mn::InputParams input;
    mn::ReadInputFile("tests_alu/test4.in", input);

    mn::OutputParams output;

    mn::FindIsotherm(1, input, output);
    std::vector<double> results = Copy(output);

    EXPECT_EQ(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected[i], results[i]);
    }
}
