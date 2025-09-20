#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <random>
#include <exception>


template <class T>
class Vector {
    size_t _dimension;
    T* _coordinates;

public:
    Vector() = delete;

    Vector(const Vector<T>& vec)
    {
        _dimension = vec._dimension;
        _coordinates = new T[_dimension * sizeof(T)];
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] = vec._coordinates[i];
        }
    }

    Vector(size_t dimention, T* coordinates) : _dimension(dimention)
    {
        _coordinates = new T[dimention * sizeof(T)];
        for (size_t i = 0; i < dimention; i++)
        {
            _coordinates[i] = coordinates[i];
        }
    }

    Vector(size_t dimention, T* start_rand, T* end_rand)
    {
        // ???
        //random_device engine;
        //uniform_int_distribution distribution(min(start_rand, end_rand), max(start_rand, end_rand));
        //for (size_t i = 0; i < vec.size(); i++)
        //{
        //    vec[i] = distribution(engine);
        //}
    }

    T operator[](const size_t pos) const
    {
        return _coordinates[pos];
    }
    T& operator[](const size_t pos)
    {
        return _coordinates[pos];
    }

    Vector<T>& operator=(const Vector<T>& rhs)
    {
        return Vector<T>(rhs);
    }

    Vector<T>& operator+=(const Vector<T>& rhs)
    {
        if (_dimension != rhs->_dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] += rhs->_coordinates[i];
        }
        return *this;
    }

    Vector<T> operator+(const Vector<T>& rhs) const
    {
        Vector<T> new_vec = *this;
        new_vec += rhs;
        return new_vec;
    }

    Vector<T>& operator-=(const Vector<T>& rhs)
    {
        if (_dimension != rhs->_dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] -= rhs->_coordinates[i];
        }
        return *this;
    }

    Vector<T> operator-(const Vector<T>& rhs) const
    {
        Vector<T> new_vec = *this;
        new_vec -= rhs;
        return new_vec;
    }

    double length() const
    {
        // Длина вектора
    }

    double operator*(const Vector<T>& rhs) const
    {
        if (_dimension != rhs._dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        double result = 0.0;
        for (size_t i = 0; i < _dimension; i++)
        {
            result += _coordinates[i] * rhs._coordinates[i];
        }
        return result;
    }

    Vector<T>& operator/=(const T a)
    {
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] /= a;
        }
        return *this;
    }

    Vector<T> operator/(const T a) const
    {
        Vector<T> new_vec = *this;
        new_vec /= a;
        return new_vec;
    }

    Vector<T>& operator*=(const T a)
    {
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] *= a;
        }
        return *this;
    }

    Vector<T> operator*(const T a) const
    {
        Vector<T> new_vec = *this;
        new_vec *= a;
        return new_vec;
    }
    friend Vector<T> operator*(T a, const Vector<T>& vec);

    ~Vector()
    {
        delete[] _coordinates;
    }
};


template <typename T>
Vector<T> operator*(T a, const Vector<T>& vec)
{
    return vec * a;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
{
    os << "( ";
    for (size_t i = 0; i < vec.dimension(); i++)
    {
        os << vec[i] << ", ";
    }
    os << ")\n";
    return os;
}

#endif
