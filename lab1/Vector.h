#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <random>
#include <complex>
#include <exception>


template <class T>
class Vector {
    size_t _dimension;
    T* _coordinates;
    inline static const double epsilon = 0.001;

public:
    Vector() = delete;

    Vector(const Vector<T>& vec)
    {
        _dimension = vec._dimension;
        _coordinates = new T[_dimension];
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] = vec._coordinates[i];
        }
    }

    Vector(size_t dimention, T* coordinates) : _dimension(dimention)
    {
        _coordinates = new T[dimention];
        for (size_t i = 0; i < dimention; i++)
        {
            _coordinates[i] = coordinates[i];
        }
    }

    Vector(size_t dimention, int start_rand, int end_rand);
    Vector(size_t dimention, float start_rand, float end_rand);
    Vector(size_t dimention, double start_rand, double end_rand);
    Vector(size_t dimention, std::complex<float> start_rand, std::complex<float> end_rand);
    Vector(size_t dimention, std::complex<double> start_rand, std::complex<double> end_rand);

    size_t dimension() const
    {
        return _dimension;
    }

    T operator[](const size_t pos) const
    {
        if (pos >= _dimension)
        {
            throw std::range_error("Index out of range");
        }
        return _coordinates[pos];
    }
    T& operator[](const size_t pos)
    {
        if (pos >= _dimension)
        {
            throw std::range_error("Index out of range");
        }
        return _coordinates[pos];
    }

    Vector<T>& operator=(const Vector<T>& rhs)
    {
        Vector<T> new_vec = Vector<T>(rhs);
        return new_vec;
    }

    Vector<T>& operator+=(const Vector<T>& rhs)
    {
        if (_dimension != rhs._dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] += rhs._coordinates[i];
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
        if (_dimension != rhs._dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        for (size_t i = 0; i < _dimension; i++)
        {
            _coordinates[i] -= rhs._coordinates[i];
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
        double len = 0.0;
        for (size_t i = 0; i < _dimension; i++)
        {
            len += _coordinates[i] * _coordinates[i];
        }
        return sqrt(len);
    }

    double operator*(const Vector<T>& rhs) const
    {
        if (_dimension != rhs._dimension)
        {
            throw std::length_error("The dimensions are not equal");
        }
        else
        {
            double result = 0.0;
            for (size_t i = 0; i < _dimension; i++)
            {
                result += _coordinates[i] * rhs._coordinates[i];
            }
            return result;
        }
    }

    Vector<T>& operator/=(const T a)
    {
        if (a == T(0))
        {
            throw std::invalid_argument("Divizion by 0");
        }
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

    friend Vector<T> operator*(const T& a, const Vector<T>& vec)
    {
        return vec * a;
    }

    bool operator==(const Vector<T>& rhs) const
    {
        if (_dimension != rhs._dimension || this->length() != rhs.length())
        {
            return false;
        }
        for (size_t i = 0; i < this->length(); i++)
        {
            double difference = abs(static_cast<double>(_coordinates[i]) - static_cast<double>(rhs._coordinates[i]));
            if (difference > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector<T>& rhs) const
    {
        return !(*this == rhs);
    }
    ~Vector()
    {
        delete[] _coordinates;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
{
    os << "( ";
    for (size_t i = 0; i < vec.dimension(); i++)
    {
        os << vec[i] << " ";
    }
    os << ")\n";
    return os;
}

template<>
inline double Vector<std::complex<float> >::operator*(const Vector<std::complex<float> >& rhs) const
{
    if (_dimension != rhs._dimension)
    {
        throw std::length_error("The dimensions are not equal");
    }

    std::complex<float> result = std::complex<float>(0, 0);
    for (size_t i = 0; i < _dimension; i++)
    {
        result += _coordinates[i] * std::conj(rhs._coordinates[i]);
    }
    return result.real();
}


template<>
inline double Vector<std::complex<double> >::operator*(const Vector<std::complex<double> >& rhs) const
{
    if (_dimension != rhs._dimension)
    {
        throw std::length_error("The dimensions are not equal");
    }

    std::complex<double> result = std::complex<double>(0, 0);
    for (size_t i = 0; i < _dimension; i++)
    {
        result += _coordinates[i] * std::conj(rhs._coordinates[i]);
    }
    return result.real();
}

template<>
inline double Vector<std::complex<float> >::length() const
{
    std::complex<float> len = std::complex<float>(0, 0);
    for (size_t i = 0; i < _dimension; i++)
    {
        len += _coordinates[i] * std::conj(_coordinates[i]);
    }
    return sqrt(len.real());

}

template<>
inline double Vector<std::complex<double> >::length() const
{
    std::complex<double> len = std::complex<double>(0, 0);
    for (size_t i = 0; i < _dimension; i++)
    {
        len += _coordinates[i] * std::conj(_coordinates[i]);
    }
    return sqrt(len.real());

}

template<>
inline bool Vector<std::complex<float> >::operator==(const Vector<std::complex<float> >& rhs) const {
    if (_dimension != rhs._dimension || this->length() != rhs.length())
    {
        return false;
    }
    for (size_t i = 0; i < _dimension; i++)
    {
        double difference_re = abs((double)_coordinates[i].real() - (double)rhs._coordinates[i].real());
        double difference_im = abs((double)_coordinates[i].imag() - (double)rhs._coordinates[i].imag());
        if (difference_re > epsilon || difference_im > epsilon)
        {
            return false;
        }
    }
    return true;
}

template<>
inline bool Vector<std::complex<double> >::operator==(const Vector<std::complex<double> >& rhs) const {
    if (_dimension != rhs._dimension || this->length() != rhs.length())
    {
        return false;
    }
    for (size_t i = 0; i < _dimension; i++)
    {
        double difference_re = abs(_coordinates[i].real() - rhs._coordinates[i].real());
        double difference_im = abs(_coordinates[i].imag() - rhs._coordinates[i].imag());
        if (difference_re > epsilon || difference_im > epsilon)
        {
            return false;
        }
    }
    return true;
}

#endif
