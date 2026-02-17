#ifndef CLASS
#define CLASS


#include <iostream>

struct People
{
    std::string _name;
    size_t _height;

    People(std::string name, size_t height) : _name(name), _height(height) {}
    bool operator<(const People rhs) const
    {
        return _height < rhs._height;
    }
    bool operator<=(const People rhs) const
    {
        return _height <= rhs._height;
    }
    bool operator>(const People rhs) const
    {
        return _height > rhs._height;
    }
    bool operator>=(const People rhs) const
    {
        return _height >= rhs._height;
    }
};



#endif
