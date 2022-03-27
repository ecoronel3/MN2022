#include <iostream>

#include "BackwardSustitution.h"
#include "GaussianElimination.h"
#include "MatrixN.h"
#include "VectorN.h"

int main()
{
	// Temp. move to test suite
	{
		mn::MatrixNf A = {{1.0f, 2.0f, 3.0f},
		                      {0.0f, 1.0f, 2.0f},
		                      {0.0f, 0.0f, 1.0f} };

		mn::VectorNf x = { 0.f, 0.f, 0.f };
		mn::VectorNf b = { 2.f, 2.f, 2.f };

		mn::BackwardSubstitution(A, b, x);

		std::cout << x << '\n';
	}

	{
		mn::MatrixNf A = {  {1.0f, 2.0f, 3.0f},
		                        {5.0f, 1.0f, 2.0f},
		                        {2.0f, 1.0f, 1.0f} };

		mn::VectorNf x = { 0.f, 0.f, 0.f };
		mn::VectorNf b = { 2.f, 2.f, 2.f };

		mn::GaussianElimination(A, b);

		std::cout << A << '\n';
		mn::BackwardSubstitution(A, b, x);
		std::cout << x << '\n';
	}

	return 0;
}
