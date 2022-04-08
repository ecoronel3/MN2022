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

        MatrixN(MatrixN const& rhs)
            : m_n(rhs.m_n)
        {
            m_data = new T[m_n*m_n]{};
            std::copy(rhs.m_data, rhs.m_data + m_n*m_n, m_data);
        }

        MatrixN(MatrixN&& rhs) 
        {
            m_n = rhs.m_n;
            m_data = rhs.m_data;
            rhs.m_n = 0;
            rhs.m_data = nullptr;
        }

        MatrixN& operator=(MatrixN const& rhs)
        {
            m_n = rhs.m_n;
            m_data = new T[m_n*m_n]{};
            std::copy(rhs.m_data, rhs.m_data + m_n*m_n, m_data);
            return *this;
        }

        MatrixN& operator=(MatrixN&& rhs)
        {
            m_n = rhs.m_n;
            m_data = rhs.m_data;
            rhs.m_n = 0;
            rhs.m_data = nullptr;

            return *this;
        }

        bool operator==(MatrixN const& rhs) const
        {
            if (m_n != rhs.m_n)
            {
                return false;
            }

            for (int i = 0; i < m_n; ++i)
            {
                for (int j = 0; j < m_n; ++j)
                {
                    if ( std::abs(this->operator()(i, j) - rhs(i, j)) > std::numeric_limits<T>::epsilon())
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool operator!=(MatrixN const& rhs) const
        {
            return !(*this == rhs);
        }

        T operator()(int i, int j) const { return m_data[m_n*i+j]; }

        T& operator()(int i, int j) { return m_data[m_n*i+j]; }

        int rows() const { return m_n; }

        int cols() const { return m_n; }

        T* get_data() { return m_data; }

        static MatrixN<T> zeros(const int n) 
        {
            MatrixN<T> m{n};
            constexpr T zero{0};
            for(int i = 0; i < n; ++i)
            {
                for(int j = 0; j < n; ++j)
                {
                    m(i, j) = zero;
                }
            }
            return m;
        }

        static MatrixN<T> identity(const int n) 
        {
            auto m = MatrixN<T>::zeros(n);
            constexpr T one{1};
            for(int i = 0; i < n; ++i)            
            {
                m(i, i) = one;
            }

            return m;
        }

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
