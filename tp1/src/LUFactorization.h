#pragma once

#include <type_traits>

#include "MatrixN.h"
#include "VectorN.h"

namespace mn
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    void LUFactorization(MatrixN<T>& A, VectorN<T>& b, MatrixN<T>& L, MatrixN<T>& U)
    {
        // TODO
    }
}
