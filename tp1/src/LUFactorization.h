#pragma once

#include <type_traits>

#include "MatrixN.h"
#include "VectorN.h"

namespace mn
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    void LUFactorization(const MatrixN<T>& A, MatrixN<T>& L, MatrixN<T>& U)
    {
        const int n = A.rows();
        U = A;
        L = MatrixN<T>::identity(n);      

        for (int i = 0; i < n-1; ++i)
        {
            const T a_ii = U(i, i);
            for (int j = i + 1; j < n; ++j)
            {
                const T a_ji = U(j, i);
                const T m_ji = a_ji/a_ii;

                for (int k = i; k < n + 1; ++k)
                {
                    U(j, k) -= m_ji * U(i, k);
                }
                L(j, i) = m_ji;
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>> >
    std::pair<MatrixN<T>, MatrixN<T>> LUFactorization(const MatrixN<T>& A)
    {
        const int n = A.rows();
        auto U = A;
        auto L = MatrixN<T>::identity(n);      

        for (int i = 0; i < n-1; ++i)
        {
            const T a_ii = U(i, i);
            for (int j = i + 1; j < n; ++j)
            {
                const T a_ji = U(j, i);
                const T m_ji = a_ji/a_ii;

                for (int k = i; k < n + 1; ++k)
                {
                    U(j, k) -= m_ji * U(i, k);
                }
                L(j, i) = m_ji;
            }
        }

        return {L, U};
    }
}
