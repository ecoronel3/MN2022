#pragma once

#include <type_traits>

#include "MatrixN.h"
#include "VectorN.h"

namespace mn
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >    
    void ForwardSubstitution(MatrixN<T> const& A, VectorN<T> const& b, VectorN<T>& x)
    {
        for (int i = 0; i < A.rows(); ++i) 
        {
            T acum{0.0};
            for (int j = 0; j < i; ++j) 
            {
                acum += x(j)*A(i, j);
            }
            x(i) = (b(i) - acum) / A(i, i);
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >    
    VectorN<T> ForwardSubstitution(const MatrixN<T>& A, const VectorN<T>& b)
    {
        auto x = VectorN<T>::zeros(b.size());
        for (int i = 0; i < A.rows(); ++i) 
        {
            T acum{0.0};
            for (int j = 0; j < i; ++j) 
            {
                acum += x(j)*A(i, j);
            }
            x(i) = (b(i) - acum) / A(i, i);
        }

        return x;
    }
}
