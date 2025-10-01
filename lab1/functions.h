#ifndef FUNCTIONS
#define FUNCTIONS

#include "Vector.h"
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

template <typename T>
void task(const Vector<T >& a, const Vector<T >& b)
{
    cout << "Task: \n";
    double angle_1 = acos((a * b) / (a.length() * b.length())) * 180.0 / 3.14159265;
    double angle_2 = 180 - angle_1;

    cout << "Vector a:\n" << a << "\n";
    cout << "Vector b:\n" << b << "\n";
    cout << "Angle 1 and 3: " << angle_1 << "\n";
    cout << "Angle 2 and 4: " << angle_2 << "\n";
}

template <typename T>
void show_methods(const Vector<T>& a, const Vector<T>& b)
{
    cout << "\nDemo Vector<T> methods\n";
    {
        cout << "Operator[]\n";
        cout << "A[0] = " << a[0] << "\n\n";
    }
    {
        cout << "Length A: " << a.length() << "\n\n";
    }
    {
        cout << "Operator =, +, +=\n";
        Vector<T> c = a;
        c = a + b;
        cout << "A + B = " << c << "\n";
    }
    {
        cout << "Operator -, -=\n";
        Vector<T> c = a;
        c -= b;
        cout << "A - B = " << c << "\n";
    }
    {
        cout << "Operator /, /=\n";
        cout << "A / 5 = " << (a / T(5)) << "\n";
    }
    {
        cout << "Operator *, *=\n";
        cout << "A * 10 = " << (a * 10) << "\n";
        cout << "10 * A = " << (10 * a) << "\n";
    }
    {
        cout << "Operator ==, != \n";
        cout << "A == B: " << (a == b) << "\n";
        cout << "A != B: " << (a != b) << "\n";
    }
}

#endif
