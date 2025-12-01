#include <iostream>
#include <random>
#include <fstream>
#include <thread>
#include "LinkedList.h"
#include "Sorting.h"

using namespace std;

template <class T>
ostream& operator<<(ostream& os, vector<T> vec)
{
    os << "{ ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        os << vec[i] << " ";
    }
    os << "}\n";
    return os;
}


ostream& operator<<(ostream& os, stats s)
{
    os << s.comparison_count << "," << s.copy_count << " \n";
    return os;
}


ostream& operator<<(ostream& os, vector<stats> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        os << vec[i] << "\n";
    }
    return os;
}



void get_average(size_t size, unsigned int seed, vector<stats>& insertion, vector<stats>& shaker, vector<stats>& quick)
{
    default_random_engine en(seed);
    uniform_int_distribution<int> dist(-100000, 100000);
    stats ins, sha, qui;
    size_t count = 5;
    vector<int> vec1(size);
    vector<int> vec2(size);
    vector<int> vec3(size);
    for (size_t k = 0; k < count; k++)
    {

        for (size_t i = 0; i < size; i++)
        {
            vec1[i] = vec2[i] = vec3[i] = dist(en);
        }

        ins += insertion_sort(vec1);
        sha += shaker_sort(vec2);
        qui += quick_sort(vec3);
    }
    insertion.push_back(ins / count);
    shaker.push_back(sha / count);
    quick.push_back(qui / count);
}


void func(vector<int>& unsorted, size_t i, vector<stats>& insertion, vector<stats>& shaker, vector<stats>& quick)
{
    vector<int> unsorted1(i*1000);
    get_average(i * 1000, i, insertion, shaker, quick);
    copy(unsorted.begin(), unsorted.begin() + i * 1000, unsorted1.begin());
    insertion.push_back(insertion_sort(unsorted1));
    insertion.push_back(insertion_sort(unsorted1));
    copy(unsorted.begin(), unsorted.begin() + i * 1000, unsorted1.begin());
    shaker.push_back(shaker_sort(unsorted1));
    shaker.push_back(shaker_sort(unsorted1));
    copy(unsorted.begin(), unsorted.begin() + i * 1000, unsorted1.begin());
    quick.push_back(quick_sort(unsorted1));
    quick.push_back(quick_sort(unsorted1));
    cout << "Complite for " << i << "\n";
}


int main()
{
    cout << "Lab3: Var 10 Task 1,1,0: by Dolzhikov D.A. 6212-100503D\n\n";

    vector<int> unsorted(50000);

    for (size_t i = 0; i < 50000; i++)
    {
        unsorted[i] = 50000 - i;
    }

    vector<stats> insertion;
    vector<stats> shaker;
    vector<stats> quick;

    vector<size_t> sizes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    thread th1(func, ref(unsorted), 25, ref(insertion), ref(shaker), ref(quick));
    thread th2(func, ref(unsorted), 50, ref(insertion), ref(shaker), ref(quick));

    for (size_t i = 0; i < sizes.size(); i++)
    {
        func(unsorted, sizes[i], insertion, shaker, quick);
    }

    th1.join();
    th2.join();

    cout << insertion << shaker << quick;
    ofstream f;
    f.open("insertion_res.txt");
    f << insertion;
    f.close();

    f.open("shaker_res.txt");
    f << shaker;
    f.close();

    f.open("quick_res.txt");
    f << quick;
    f.close();

    LinkedList<int> list;
    list.push_tail(4);
    list.push_tail(67);
    list.push_tail(2);
    list.push_tail(76);
    list.push_tail(2);
    list.push_tail(7);
    list.push_tail(4);
    list.push_tail(89);
    list.push_tail(1);
    list.push_tail(7);
    list.push_tail(55);
    list.push_tail(7);

    cout << "Original list: " << list << endl;

    stats list_stats = insertion_sort(list);
    cout << "Sorted list: " << list << endl;
    cout << "List insertion sort: " << list_stats.comparison_count << " comparisons, " << list_stats.copy_count << " copies\n";

    return 0;
}
