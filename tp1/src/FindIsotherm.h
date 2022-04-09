#pragma once

#include "BackwardSustitution.h"
#include "ForwardSubstitution.h"
#include "GaussianElimination.h"
#include "MatrixN.h"
#include "Parameters.h"
#include "VectorN.h"
#include "LUFactorization.h"

namespace mn
{
    constexpr float pi = 3.141592653589793f;

    std::pair<MatrixNf, VectorNf> BuildEqSystem(float ri, float re, int m, int n, const std::vector<float>& internalTemps, const std::vector<float>& externalTemps)
    {
        auto A = MatrixNf::zeros(n * (m - 1));
        auto b = VectorNf::zeros(n * (m - 1));
        
        const float deltaTheta = 2.0f * pi / static_cast<float>(n);
        const float sqDeltaTheta = deltaTheta * deltaTheta;

        // const double deltaRadius = (re - ri) / (static_cast<double>(m) + 1.0);
        const float deltaRadius = (re - ri) / static_cast<float>(m);
        const float sqDeltaRadius = deltaRadius * deltaRadius;

        // caso especial j = 1
        float radius = ri+deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            const int j = 1;
            const int row = k;
            const float sqRadius = radius * radius;

            b(k) = -(internalTemps[k] * (sqRadius - radius * deltaRadius ) * sqDeltaTheta );

            A(row, (n + ((k-1)%n)) % n) = sqDeltaRadius;

            A(row, row) = -2.0f*sqRadius*sqDeltaTheta + radius*deltaRadius*sqDeltaTheta - 2.0f*sqDeltaRadius;

            A(row, (n + ((k+1)%n)) % n) = sqDeltaRadius;
            A(row, row + n) = sqRadius*sqDeltaTheta;
        }

        // caso especial j = m - 1
        radius = re - deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            //const int j = m - 1;
            const int row = n*(m - 2) + k;
            const float sqRadius = radius * radius;

            A(row, row - n) = (sqRadius - radius*deltaRadius)*sqDeltaTheta;
            A(row, n*(m-2) + (n + ((k-1)%n)) % n) = sqDeltaRadius;
            A(row, row) = -2.0f*sqRadius*sqDeltaTheta + radius*deltaRadius*sqDeltaTheta - 2.0f*sqDeltaRadius;
            A(row, n*(m-2) + (n + ((k+1)%n)) % n) = sqDeltaRadius;

            b(row) = -externalTemps[k]*sqRadius*sqDeltaTheta;
        }

        for (int j = 2; j < m - 1; ++j)
        {
            radius = ri + deltaRadius * j;
            const float sqRadius = radius * radius;

            for (int k = 0; k < n; ++k)
            {
                const auto row = n * (j - 1) + k;
                A(row, row - n) = (sqRadius - radius*deltaRadius)*sqDeltaTheta;
                A(row, n*(j-1) + (n + ((k-1)%n)) % n) = sqDeltaRadius;
                A(row, row) = -2.0f*sqRadius*sqDeltaTheta + radius*deltaRadius*sqDeltaTheta - 2.0f*sqDeltaRadius;
                A(row, n*(j-1) + (n + ((k+1)%n)) % n) = sqDeltaRadius;
                A(row, row + n) = sqRadius*sqDeltaTheta;
            }
        }

        return {A, b};
    }

    inline void FindIsotherm(const int method, const InputParams& input, OutputParams& output)
    {
        for (const Instance& inst: input.instances)
        {
            auto [A, b] = BuildEqSystem(input.ri, input.re, input.m, input.n, inst.internalTemps, inst.externalTemps);
            auto x = VectorNf::zeros(b.size());

            if (method == 0)
            {
                GaussianElimination(A, b);
                BackwardSubstitution(A, b, x);

            }
            else if (method == 1)
            {
                auto [L, U] = LUFactorization(A);
                VectorNf y = ForwardSubstitution(L, b);                
                BackwardSubstitution(U, y, x);
            }
            
            output.solucion = x;
        }
    }
}
