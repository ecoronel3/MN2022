#pragma once

#include <type_traits>

#include "MatrixN.h"
#include "VectorN.h"

namespace mn
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    void GaussianElimination(MatrixN<T>& A, VectorN<T>& b)
    {
        const int rows = A.rows();
        const int cols = A.cols();

        for (int k = 0; k < rows-1; ++k)
        {
            const T c_kk = A(k, k);
            for (int i = k + 1; i < cols; ++i)
            {
                const T c_ik = A(i, k);
                const T m = c_ik/c_kk;

                for (int j = 0; j < cols; ++j)
                {
                    A(i, j) -= A(k, j)*m;
                }
                b(i) -= b(k)*m;
            }
        }
    }
}
