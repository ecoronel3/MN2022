#pragma once

#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <cstring>

namespace mn
{
    template<typename T,
        typename = std::enable_if_t<std::is_floating_point_v<T>> >
    class VectorN
    {
        T* m_data = nullptr;
        int m_size = 0;
    public:
        VectorN() = default;

        explicit VectorN(const int size)
            : m_data(nullptr)
            , m_size(size)
        {
            m_data = new T[m_size]{};
        }

        VectorN(std::initializer_list<T> l)
            : m_data(nullptr)
            , m_size(static_cast<int>(l.size()))
        {
            m_data = new T[m_size];
            int i = 0;
            for(auto& e: l)
            {
                m_data[i++] = e;
            }
        }

        ~VectorN()
        {
            delete[] m_data;
            m_data = nullptr;
        }

        VectorN(VectorN const& rhs)
            : m_size(rhs.m_size)
        {
            m_data = new T[m_size]{};
            std::memcpy(m_data, rhs.m_data, m_size*sizeof(T));
        }

        VectorN(VectorN&& rhs)
            : m_data(rhs.m_data)
            , m_size(rhs.m_size)
        {
            rhs.m_size = 0;
            rhs.m_data = nullptr;
        }

        VectorN& operator=(const VectorN& rhs)
        {
            m_size = rhs.m_size;
            m_data = new T[m_size]{};
            std::memcpy(m_data, rhs.m_data, m_size*sizeof(T));
            return *this;
        }
        
        VectorN& operator=(VectorN&& rhs)
        {
            m_size = rhs.m_size;
            m_data = rhs.m_data;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
            return *this;
        }

        T operator()(int i) const { return m_data[i]; }

        T& operator()(int i) { return m_data[i]; }

        bool operator==(const VectorN& rhs) const
        {
            if (m_size != rhs.m_size)
            {
                return false;
            }

            for (int i = 0; i < m_size; ++i)
            {
                if ( std::abs(this->operator()(i) - rhs(i)) > std::numeric_limits<T>::epsilon())
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const VectorN& rhs) const
        {
            return !(*this == rhs);
        }

        int size() const { return m_size; }

        T* get_data() { return m_data; }

        static VectorN<T> zeros(const int size) 
        {
            VectorN<T> v(size);
            constexpr T zero{0};
            for(int i = 0; i < size; ++i)
            {
                v(i) = zero;
            }
            return v;
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, VectorN<T> const& vec)
    {
        os << '[';
        for(int i=0; i<vec.size(); ++i) 
        {
            os << vec(i) << ' ';
        }
        os << ']';
        return os;
    }

    template <>
    inline std::ostream& operator<<(std::ostream& os, VectorN<float> const& vec)
    {
        os << std::fixed << std::setprecision(5);
        os << '[';
        for(int i=0; i<vec.size(); ++i) 
        {
            os << vec(i) << ' ';
        }
        os << ']';
        return os;
    }

    using VectorNf = VectorN<float>;
    using VectorNd = VectorN<double>;
}
