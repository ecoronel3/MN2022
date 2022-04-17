#pragma once

#include "FPType.h"
#include "BackwardSustitution.h"
#include "ForwardSubstitution.h"
#include "GaussianElimination.h"
#include "LUFactorization.h"
#include "MatrixN.h"
#include "Parameters.h"
#include "VectorN.h"

namespace mn
{
    constexpr FPType pi = 3.141592653589793;

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    inline MatrixN<T> BuildMatrix(T ri, T re, int m, int n)
    {
        auto A = MatrixN<T>::zeros(n * (m - 1));
        
        const T deltaTheta = 2.0f * pi / static_cast<T>(n);
        const T sqDeltaTheta = deltaTheta * deltaTheta;

        const T deltaRadius = (re - ri) / static_cast<T>(m);
        const T sqDeltaRadius = deltaRadius * deltaRadius;

        // caso especial j = 1
        T radius = ri+deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            const int j = 1;
            const int row = k;
            const T sqRadius = radius * radius;

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
            const T sqRadius = radius * radius;

            A(row, row - n) = (sqRadius - radius*deltaRadius)*sqDeltaTheta;
            A(row, n*(m-2) + (n + ((k-1)%n)) % n) = sqDeltaRadius;
            A(row, row) = -2.0f*sqRadius*sqDeltaTheta + radius*deltaRadius*sqDeltaTheta - 2.0f*sqDeltaRadius;
            A(row, n*(m-2) + (n + ((k+1)%n)) % n) = sqDeltaRadius;
        }

        for (int j = 2; j < m - 1; ++j)
        {
            radius = ri + deltaRadius * j;
            const T sqRadius = radius * radius;

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

        return A;
    }

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    inline VectorN<T> BuildVector(T ri, T re, int m, int n, const std::vector<T>& internalTemps, const std::vector<T>& externalTemps)
    {
        auto b = VectorN<T>::zeros(n * (m - 1));
        
        const T deltaTheta = 2.0f * pi / static_cast<T>(n);
        const T sqDeltaTheta = deltaTheta * deltaTheta;
        const T deltaRadius = (re - ri) / static_cast<T>(m);

        // caso especial j = 1
        T radius = ri+deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            const T sqRadius = radius * radius;
            b(k) = -(internalTemps[k] * (sqRadius - radius * deltaRadius ) * sqDeltaTheta );
        }

        // caso especial j = m - 1
        radius = re - deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            const T sqRadius = radius * radius;
            b(n*(m - 2) + k) = -externalTemps[k]*sqRadius*sqDeltaTheta;
        }

        return b;
    }

    inline void FindIsothermEG(const InputParams& input, OutputParams& output)
    {
        output.temps.reserve(input.ninst);
        for (const Instance& inst: input.instances)
        {
            auto A = BuildMatrix<FPType>(input.ri, input.re, input.m, input.n);
            auto b = BuildVector<FPType>(input.ri, input.re, input.m, input.n, inst.internalTemps, inst.externalTemps);
            auto x = VectorN<FPType>::zeros(b.size());
            GaussianElimination(A, b);
            BackwardSubstitution(A, b, x);
            auto& temps = output.temps.emplace_back();
            temps.internal = inst.internalTemps;
            temps.inner = x;
            temps.external = inst.externalTemps;
        }
    }

    inline void FindIsothermLU(const InputParams& input, OutputParams& output)
    {
        auto A = BuildMatrix<FPType>(input.ri, input.re, input.m, input.n);
        output.temps.reserve(input.ninst);
        auto [L, U] = LUFactorization(A);

        for (const Instance& inst: input.instances)
        {
            auto b = BuildVector<FPType>(input.ri, input.re, input.m, input.n, inst.internalTemps, inst.externalTemps);

            auto x = VectorN<FPType>::zeros(b.size());            
            VectorN<FPType> y = ForwardSubstitution(L, b);
            BackwardSubstitution(U, y, x);

            auto& temps = output.temps.emplace_back();
            temps.internal = inst.internalTemps;
            temps.inner = x;
            temps.external = inst.externalTemps;
        }
    }

    inline void FindIsotherm(const int method, const InputParams& input, OutputParams& output)
    {
        if (method == 0)
        {
            FindIsothermEG(input, output);
        }
        else if (method == 1)
        {
            FindIsothermLU(input, output);
        }
    }
}
