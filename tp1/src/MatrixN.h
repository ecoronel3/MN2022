#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iomanip>

namespace mn 
{
    template <typename T,
        typename = std::enable_if_t<std::is_floating_point_v<T>> >
    class MatrixN
    {
        T* m_data = nullptr;
        int m_n = 0;
    public:
        explicit MatrixN(const int n)
            : m_data(nullptr)
            , m_n(n)
        {
            m_data = new T[m_n*m_n]{};
        }

        MatrixN(std::initializer_list<std::initializer_list<T>> lst)
                : m_data(nullptr)
                , m_n(0)
        {
            m_n = static_cast<int>(lst.size());

            m_data = new T[m_n*m_n];
            int i{0}, j{0};
            for (auto& ls: lst) 
            {
                for (auto& e: ls) 
                {
                    m_data[i*m_n+j] = e;
                    ++j;
                }
                ++i;
                j = 0;
            }
        }

        ~MatrixN() 
        {
            delete [] m_data;
            m_data = nullptr;
        }

        MatrixN(MatrixN const&) = delete;
        MatrixN(MatrixN&&) = delete;
        void operator=(MatrixN const&) = delete;
        void operator=(MatrixN&&) = delete;

        T operator()(int i, int j) const { return m_data[m_n*i+j]; }

        T& operator()(int i, int j) { return m_data[m_n*i+j]; }

        int rows() const { return m_n; }

        int cols() const { return m_n; }

        T* get_data() { return m_data; }
    };

    template <typename T>
    inline std::ostream& operator<<(std::ostream& os, MatrixN<T> const& geMatrix)
    {
        os << '[';
        for(int i=0; i<geMatrix.rows(); ++i) 
        {
            os << '[';
            for(int j=0; j<geMatrix.cols(); ++j) 
            {
                os << geMatrix(i, j) << ' ';
            }
            os << ']';
            os << '\n';
        }
        os << ']';
        return os;
    }

    template <>
    inline std::ostream& operator<<(std::ostream& os, MatrixN<float> const& geMatrix) 
    {
        os << std::fixed << std::setprecision(5);
        os << '[';
        for(int i=0; i<geMatrix.rows(); ++i) 
        {
            os << '[';
            for(int j=0; j<geMatrix.cols(); ++j) 
            {
                os << geMatrix(i, j) << ' ';
            }
            os << ']';
            os << '\n';
        }
        os << ']';
        return os;
    }

    using MatrixNf = MatrixN<float>;
    using MatrixNd = MatrixN<double>;
}
