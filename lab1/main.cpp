#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
    complex<float> coords_a[] = { 1.5, 2, 3 };
    complex<float> coords_b[] = { 3, 2.5, 1 };

    Vector< complex<float> > a(3, coords_a);
    Vector< complex<float> > b(3, complex<float>(3, 2), complex<float>(1,2));

    double angle_1 = acos((a * b) / (a.length() * b.length()));
    double angle_2 = 180 - angle_1;

    Vector < complex<float> > c = a + b;

    cout << a << b << angle_1 << " " << angle_2 << "\n";

    cout << c;

    return 0;
}
