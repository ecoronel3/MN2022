#pragma once

#include "BackwardSustitution.h"
#include "GaussianElimination.h"
#include "MatrixN.h"
#include "Parameters.h"
#include "VectorN.h"
#include <cmath>

namespace mn
{
    constexpr auto pi = 3.141592653589793;

    inline void FindIsotherm(float ri, float re, int n, int m, const std::vector<float>& internalTemps, const std::vector<float>& externalTemps)
    {
        // Build Eq System.
        const double deltaTheta = 2.0 * pi / static_cast<double>(n);
        const double deltaRadius = (re - ri) / (static_cast<double>(m) + 1.0);

        MatrixNf A{ n * (m - 1) };
        VectorNf b(  n * (m - 1) );

        std::cout << "Matriz de " << n * (m - 1) << " x " << n * (m - 1) << '\n';
        std::cout << "=============================================\n";

        // TODO: caso especial j = 1
        double radius = ri+deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n*(m-1); i++) {
                A(k,i) = 0.0;
            }
            const int j = 1;
            const int row = k;
            b(k) = -(internalTemps[k] * pow(radius*deltaTheta,2) - radius * deltaRadius * pow(deltaTheta, 2));

            std::cout << "b(" << k << ") = t(" << j - 1 << ", " << k << ")\n";

            //(b + (a%b)) % b
            A(row, (n + ((k-1)%n)) % n) = pow(deltaRadius,2);
            std::cout << "A(" << k << ", " << n * (j - 1) + k - 1 << ") = t(" << j << ", " << k - 1 << ")\n";

            A(row, row) = (-2)*pow(radius*deltaTheta,2) + radius*deltaRadius*pow(deltaTheta,2)
                    - 2*pow(deltaRadius,2);

            std::cout << "A(" << k << ", " << n * (j - 1) + k << ") = t(" << j << ", " << k << ")\n";

            A(row, (n + ((k+1)%n)) % n) = pow(deltaRadius, 2);
            std::cout << "A(" << k << ", " << n * (j - 1) + k + 1 << ") = t(" << j << ", " << k + 1 << ")\n";

            A(row, row + n) = pow(radius*deltaTheta,2);
            std::cout << "A(" << k << ", " << n * j + k << ") = t(" << j + 1 << ", " << k << ")\n";
            std::cout << "=============================================\n";
        }

        // TODO: caso especial j = m - 1
        radius = re - deltaRadius;
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n*(m-1); i++) {
                A(k,i) = 0.0;
            }

            //const int j = m - 1;
            const int row = n*(m - 2) + k;

            A(row, row - n) = pow(radius*deltaTheta,2) - radius*deltaRadius*pow(deltaTheta,2);
            A(row, n*(m-2) + (n + ((k-1)%n)) % n) = pow(deltaRadius,2);
            A(row, row) = (-2)*pow(radius*deltaTheta,2) + radius*deltaRadius*pow(deltaTheta,2)
                          - 2*pow(deltaRadius,2);
            A(row, n*(m-2) + (n + ((k+1)%n)) % n) = pow(deltaRadius,2);
            b(row) = -pow(radius*deltaTheta,2)*externalTemps[k];
        }

        for (int j = 2; j < m - 1; ++j)
        {
            radius = ri + deltaRadius * j;


            // t_jm1k
            // t_jk            
            // t_jp1

            // t_jkm1
            // t_jkp1

            // a11*t10 + a12*t11 + a13*t12 + a14*t13 + a15*t20 + a16*t21 + a17*t22 + a18*t23 + a19*t30 + a1A*t31 + a1B*t32 + a1C*t33

            // t_jm1k + t_jkm1 + t_jk + t_jkp1 + t_jp1k
            // a73*t12 + a76*t21 + a77*t22 + a78*t23 + a7B*t32

            for (int k = 0; k < n; ++k)
            {
                const auto row = n * (j - 1) + k;
                b(row) = 0.0;
                A(row, row - n) = pow(radius*deltaTheta,2) - radius*deltaRadius*pow(deltaTheta,2);
                A(row, n*(j-1) + (n + ((k-1)%n)) % n) = pow(deltaRadius,2);
                A(row, row) = (-2)*pow(radius*deltaTheta,2) + radius*deltaRadius*pow(deltaTheta,2)
                              - 2*pow(deltaRadius,2);
                A(row, n*(j-1) + (n + ((k+1)%n)) % n) = pow(deltaRadius,2);
                A(row, row + n) = pow(radius*deltaTheta,2);


                std::cout << "A(" << row << ", " << n * (j - 2) + k << ") = t(" << j - 1 << ", " << k << ")\n";

                // A(n*(j-1) + k, n*(j-1) + k - 1) = coef(t_jkm1)
                std::cout << "A(" << row << ", " << n * (j - 1) + k - 1 << ") = t(" << j << ", " << k - 1 << ")\n";

                // A(n*(j-1) + k, n*(j-1) + k) = coef(t_jk)
                std::cout << "A(" << row << ", " << n * (j - 1) + k << ") = t(" << j << ", " << k << ")\n";

                // A(n*(j-1) + k, n*(j-1) + k + 1) = coef(t_jkp1)
                std::cout << "A(" << row << ", " << n * (j - 1) + k + 1 << ") = t(" << j << ", " << k + 1 << ")\n";

                // A(n*(j-1) + k, n*j + k) = coef(t_jp1k)
                std::cout << "A(" << row << ", " << n * j + k << ") = t(" << j + 1 << ", " << k << ")\n";

                std::cout << "=============================================\n";
            }
        }
    }

    inline void FindIsotherm(const InputParams& input, OutputParams& output)
    {
        // TODO
        for (const Instance& inst: input.instances)
        {
            FindIsotherm(input.ri, input.re, input.n, input.m, inst.internalTemps, inst.externalTemps);
        }
    }
}
