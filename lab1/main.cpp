#include <iostream>
#include "Vector.h"
#include "functions.h"

using namespace std;

int main()
{
    cout << "Lab1: Var 1 Task 3: by Dolzhikov D.A. 6212-100503D\n\n";
    cout << "Input the dimension of the vector ( > 0): ";
    size_t dimension = 0;
    cin >> dimension;
    if (!dimension)
    {
        cerr << "ERROR: Wrong input";
        return -1;
    }
    cout << "Select the data type\n[1] - int\n[2] - float\n[3] - double\n[4] - std::complex<float>\n[5] - std::complex<double>\n";
    size_t choice = 0;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int* coords_a = new int[dimension];
        cout << "Input coordinates for Vector<int> a:\n";

        for (size_t i = 0; i < dimension; i++)
        {
            cin >> coords_a[i];
        }

        Vector<int> a(dimension, coords_a);

        int start_rand = 0, end_rand = 0;
        cout << "Input a range of random numbers (start, end) for Vector<int> \nInput start: ";
        cin >> start_rand;
        cout << "Input end: ";
        cin >> end_rand;
        Vector<int> b(dimension, start_rand, end_rand);

        task(a, b);
        show_methods(a, b);

        break;
    }
    case 2:
    {
        float* coords_a = new float[dimension];
        cout << "Input coordinates for Vector<float> a:\n";

        for (size_t i = 0; i < dimension; i++)
        {
            cin >> coords_a[i];
        }

        Vector<float> a(dimension, coords_a);

        float start_rand = 0, end_rand = 0;
        cout << "Input a range of random numbers for Vector<float> (start, end)\nInput start: ";
        cin >> start_rand;
        cout << "Input end: ";
        cin >> end_rand;
        Vector<float> b(dimension, start_rand, end_rand);

        task(a, b);
        show_methods(a, b);

        break;
    }
    case 3:
    {
        double* coords_a = new double[dimension];
        cout << "Input coordinates for Vector<double> a:\n";

        for (size_t i = 0; i < dimension; i++)
        {
            cin >> coords_a[i];
        }

        Vector<double> a(dimension, coords_a);

        double start_rand = 0, end_rand = 0;
        cout << "Input a range of random numbers (start, end) for Vector<double> b\nInput start: ";
        cin >> start_rand;
        cout << "Input end: ";
        cin >> end_rand;
        Vector<double> b(dimension, start_rand, end_rand);

        task(a, b);
        show_methods(a, b);

        break;
    }
    case 4:
    {
        complex<float>* coords_a = new complex<float>[dimension];
        cout << "Input coordinates for Vector<complex<float>> a:\n";

        for (size_t i = 0; i < dimension; i++)
        {
            float re = 0, im = 0;
            cout << "Input real: ";
            cin >> re;
            cout << "Input image: ";
            cin >> im;
            coords_a[i] = complex(re, im);
        }

        Vector<complex<float> > a(dimension, coords_a);

        complex<float> start_rand = 0, end_rand = 0;
        cout << "Input a range of random numbers (start, end) for Vector<complex<float>> b\nInput start: ";
        float re = 0, im = 0;
        cout << "Input real: ";
        cin >> re;
        cout << "Input image: ";
        cin >> im;
        start_rand = complex(re, im);

        cout << "Input end: ";
        cout << "Input real: ";
        cin >> re;
        cout << "Input image: ";
        cin >> im;
        end_rand = complex(re, im);
        Vector<complex<float> > b(dimension, start_rand, end_rand);

        task(a, b);
        show_methods(a, b);

        break;
    }
    case 5:
    {
        complex<double>* coords_a = new complex<double>[dimension];
        cout << "Input coordinates for Vector<complex<double>> a:\n";

        for (size_t i = 0; i < dimension; i++)
        {
            double re = 0, im = 0;
            cout << "Input real: ";
            cin >> re;
            cout << "Input image: ";
            cin >> im;
            coords_a[i] = complex(re, im);
        }

        Vector<complex<double> > a(dimension, coords_a);

        complex<double> start_rand = 0, end_rand = 0;
        cout << "Input a range of random numbers (start, end) for Vector<complex<double>> b\nInput start: ";
        double re = 0, im = 0;
        cout << "Input real: ";
        cin >> re;
        cout << "Input image: ";
        cin >> im;
        start_rand = complex(re, im);

        cout << "Input end: ";
        cout << "Input real: ";
        cin >> re;
        cout << "Input image: ";
        cin >> im;
        end_rand = complex(re, im);
        Vector<complex<double> > b(dimension, start_rand, end_rand);
        
        task(a, b);
        show_methods(a, b);

        break;
    }
    default:
        cerr << "ERROR: Wrong input!\n";
        return -1;
        break;
    }


    return 0;
}
