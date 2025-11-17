#ifndef MYSORT
#define MYSORT

#include <iostream>
#include <vector>
#include "LinkedList.h"


struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;
};


template <class T>
stats insertion_sort(std::vector<T>& vec);

template <class T>
stats insertion_sort(LinkedList<T>& list);

template <class T>
stats shaker_sort(std::vector<T>& vec);

template <class T>
stats quick_sort(std::vector<T>& vec);

template <class T>
void quick_sort(std::vector<T>& vec, size_t start, size_t end, stats& s);

template <class T>
void part_quick_sort(std::vector<T>& vec, size_t start, size_t end, stats& s);

#endif 
