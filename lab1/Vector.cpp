#include "Vector.h"


Vector<int>::Vector(size_t dimension, int start_rand, int end_rand)
{
    _dimension = dimension;
    _coordinates = new int[_dimension];
    std::random_device engine;
    std::uniform_int_distribution distribution(std::min(start_rand, end_rand), std::max(start_rand, end_rand));
    for (size_t i = 0; i < dimension; i++)
    {
        _coordinates[i] = distribution(engine);
    }
}

Vector<float>::Vector(size_t dimension, float start_rand, float end_rand)
{
    _dimension = dimension;
    _coordinates = new float[_dimension];
    std::random_device engine;
    std::uniform_real_distribution distribution(std::min(start_rand, end_rand), std::max(start_rand, end_rand));
    for (size_t i = 0; i < dimension; i++)
    {
        _coordinates[i] = distribution(engine);
    }
}
Vector<double>::Vector(size_t dimension, double start_rand, double end_rand)
{
    _dimension = dimension;
    _coordinates = new double[_dimension];
    std::random_device engine;
    std::uniform_real_distribution distribution(std::min(start_rand, end_rand), std::max(start_rand, end_rand));
    for (size_t i = 0; i < dimension; i++)
    {
        _coordinates[i] = distribution(engine);
    }
}
Vector< std::complex<float> >::Vector(size_t dimension, std::complex<float> start_rand, std::complex<float> end_rand)
{
    _dimension = dimension;
    _coordinates = new std::complex<float>[_dimension];
    std::random_device engine;
    std::uniform_real_distribution distributionre(std::min(start_rand.real(), end_rand.real()), std::max(start_rand.real(), end_rand.real()));
    std::uniform_real_distribution distributionim(std::min(start_rand.imag(), end_rand.imag()), std::max(start_rand.imag(), end_rand.imag()));
    for (size_t i = 0; i < dimension; i++)
    {
        _coordinates[i] = std::complex<float>(distributionre(engine), distributionim(engine));
    }
}
Vector< std::complex<double> >::Vector(size_t dimension, std::complex<double> start_rand, std::complex<double> end_rand)
{
    _dimension = dimension;
    _coordinates = new std::complex<double>[_dimension];
    std::random_device engine;
    std::uniform_real_distribution distributionre(std::min(start_rand.real(), end_rand.real()), std::max(start_rand.real(), end_rand.real()));
    std::uniform_real_distribution distributionim(std::min(start_rand.imag(), end_rand.imag()), std::max(start_rand.imag(), end_rand.imag()));
    for (size_t i = 0; i < dimension; i++)
    {
        _coordinates[i] = std::complex<double>(distributionre(engine), distributionim(engine));
    }
}

