#include <filesystem>
#include <iostream>

#include "FileHelper.h"
#include "FindIsotherm.h"

using FPType = double;

int main(const int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Cantidad de parametros invalida. Se esperaban 3 parametros.\n";
		return -1;
	}

	std::filesystem::path inputFile = argv[1];
	std::filesystem::path outputFile = argv[2];
	const int method = std::atoi(argv[3]);

	if (method == 0 // GaussianElimination
		|| method == 1) // LU Factorization
	{
		mn::InputParams iParams;
		if (mn::ReadInputFile(inputFile, iParams))
		{
			mn::OutputParams oParams;
			mn::FindIsotherm(method, iParams, oParams);
			mn::WriteOutputFile(outputFile, oParams);
		}
	}
	else
	{
		std::cerr << "Metodo selecionado invalido. 0 = EG, 1 = LU.\n";
		return -1;
	}

	return 0;
}
