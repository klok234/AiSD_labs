#include <chrono>
#include "Set.h"

using namespace std;

void get_stats_for_set()
{
    vector<int> sizes = { 1000, 10000, 100000};

    for (auto& size : sizes)
    {
        auto duration = 0ms;
        for (size_t j = 0; j < 100; j++)
        {
            Set test;
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < size;)
            {
                i += test.insert(lcg()) ? 1 : 0;
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for inserting in set " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 100) << "\n";
    }
    cout << "====================================================================\n";
    for (auto& size : sizes)
    {
        auto duration = 0ms;
        Set test;

        for (size_t i = 0; i < size;)
        {
            i += test.insert(lcg()) ? 1 : 0;
        }

        for (size_t j = 0; j < 1000; j++)
        {
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < 10000; i++)
            {
                bool res = test.contains(lcg());
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for searching in set with " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 1000) << "\n";
    }
    cout << "====================================================================\n";
    for (auto& size : sizes)
    {
        auto duration = 0ms;
        Set test;

        for (size_t i = 0; i < size;)
        {
            i += test.insert(lcg()) ? 1 : 0;
        }

        for (size_t j = 0; j < 1000; j++)
        {
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < 10000; i++)
            {
                test.insert(lcg());
                test.erase(lcg());
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for insert and erase in set with " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 1000) << "\n";
    }
    cout << "====================================================================\n";
}


void get_stats_for_vector()
{
    vector<int> sizes = { 1000, 10000, 100000 };

    for (auto& size : sizes)
    {
        auto duration = 0ms;
        for (size_t j = 0; j < 100; j++)
        {
            vector<int> test;
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < size; i++)
            {
                test.push_back(lcg());
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for inserting in vector " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 100) << "\n";
    }
    cout << "====================================================================\n";
    for (auto& size : sizes)
    {
        auto duration = 0ms;
        vector<int> test;

        for (size_t i = 0; i < size; i++)
        {
            test.push_back(lcg());
        }

        for (size_t j = 0; j < 100; j++)
        {
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < 10000; i++)
            {
                bool res = (std::find(test.begin(), test.end(), lcg()) != test.end());
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for searching in vector with " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 100) << "\n";
    }
    cout << "====================================================================\n";
    for (auto& size : sizes)
    {
        auto duration = 0ms;
        vector<int> test;

        for (size_t i = 0; i < size; i++)
        {
            test.push_back(lcg());
        }

        for (size_t j = 0; j < 10; j++)
        {
            auto start = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < 10000; i++)
            {
                test.push_back(lcg());
                try
                {
                    auto p = find(test.begin(), test.end(), lcg());
                    if (p == test.end()) continue;

                    test.erase(p);
                }
                catch (const std::exception&)
                {
                    continue;
                }
            }
            auto stop = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::milliseconds>(stop - start);

        }
        cout << "Duration for insert and erase in vector with " << size << " elements: " << chrono::duration_cast<chrono::milliseconds>(duration / 10) << "\n";
    }
    cout << "====================================================================\n";
}

size_t lcg(){
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
