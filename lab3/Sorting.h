#ifndef MYSORT
#define MYSORT

#include <iostream>
#include <vector>
#include "LinkedList.h"

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;

    stats& operator+=(const stats& rhs)
    {
        comparison_count += rhs.comparison_count;
        copy_count += rhs.copy_count;
        return *this;
    }

    stats operator/(const size_t scalar)
    {
        stats tmp(*this);
        tmp.comparison_count /= scalar;
        tmp.copy_count /= scalar;
        return tmp;
    }
};

template <class T>
stats insertion_sort(std::vector<T>& vec)
{
    stats s;
    for (int i = 1; i < vec.size(); i++)
    {
        int sorted = i - 1;
        ++s.comparison_count;
        while (sorted > -1 && vec[sorted] > vec[sorted + 1])
        {
            ++s.comparison_count;
            std::swap(vec[sorted], vec[sorted + 1]);
            s.copy_count += 3;
            --sorted;
        }
    }
    return s;
}


template <class T>
stats insertion_sort(LinkedList<T>& list)
{
    stats s;
    for (int i = 1; i < list.size(); i++)
    {
        int sorted = i - 1;
        ++s.comparison_count;
        while (sorted > -1 && list[sorted] > list[sorted + 1])
        {
            ++s.comparison_count;
            std::swap(list[sorted], list[sorted + 1]);
            s.copy_count += 3;
            --sorted;
        }
    }
    return s;
}

template <class T>
stats shaker_sort(std::vector<T>& vec)
{
    stats s;

    int left = 1;
    int right = vec.size() - 1;
    while (left <= right)
    {
        for (int i = left; i <= right; ++i) {
            ++s.comparison_count;
            if (vec[i - 1] > vec[i])
            {
                std::swap(vec[i - 1], vec[i]);
                s.copy_count += 3;
            }
        }
        --right;

        for (int i = right; i >= left; --i) {
            ++s.comparison_count;
            if (vec[i - 1] > vec[i])
            {
                std::swap(vec[i - 1], vec[i]);
                s.copy_count += 3;
            }
        }
        ++left;
    }

    return s;
}

template <class T>
int part_quick_sort(std::vector<T>& vec, int left, int right, stats& s)
{
    T pivot = vec[(left + right) / 2];
    while (left <= right)
    {
        while (vec[left] < pivot)
        {
            ++left;
            ++s.comparison_count;
        }
        while (vec[right] > pivot)
        {
            --right;
            ++s.comparison_count;
        }
        if (left <= right)
        {
            std::swap(vec[left], vec[right]);
            ++left;
            --right;
            s.copy_count += 3;
        }
    }
    return left;
}

template <class T>
void quick_sort(std::vector<T>& vec, int start, int end, stats& s)
{
    if (start >= end)
    {
        return;
    }
    int right_start = part_quick_sort(vec, start, end, s);
    quick_sort(vec, start, right_start - 1, s);
    quick_sort(vec, right_start, end, s);
}

template <class T>
stats quick_sort(std::vector<T>& vec)
{
    stats s;
    if (!vec.empty()) {
        quick_sort(vec, 0, vec.size() - 1, s);
    }
    return s;
}

#endif
