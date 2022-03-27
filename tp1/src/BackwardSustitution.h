#pragma once

#include <type_traits>

#include "MatrixN.h"
#include "VectorN.h"

namespace mn
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    void BackwardSubstitution(MatrixN<T> const& A, VectorN<T> const& b, VectorN<T>& x)
    {
        for (int i = A.rows()-1; i >= 0; --i) 
        {
            T acum{0.0};
            for (int j = i+1; j < A.cols(); ++j) 
            {
                acum += x(j)*A(i, j);
            }
            x(i) = (b(i) - acum) / A(i, i);
        }
    }
}
