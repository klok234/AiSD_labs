#include "Sorting.h"

using namespace std;

template <class T>
stats insertion_sort(std::vector<T>& vec)
{
    stats s;
    for (size_t i = 1; i < vec.size(); i++)
    {
        size_t sorted = i - 1;
        while (sorted > -1 && vec[sorted] > vec[sorted + 1])
        {
            ++s.comparison_count;
            swap(vec[sorted], vec[sorted + 1]);
            s.copy_count += 3;
            --sorted;
        }
    }
    return s;
}

template <class T>
stats insertion_sort(LinkedList<T>& list)
{
    return stats();
}

template <class T>
stats shaker_sort(std::vector<T>& vec)
{
    stats s;

    size_t left = 1;
    size_t right = vec.size() - 1;
    while (left <= right)
    {
        for (size_t i = left; i <= right; ++i) {
            ++s.comparison_count;
            if (vec[i - 1] > vec[i])
            {
                swap(vec[i - 1], vec[i]);
                s.copy_count += 3;
            }
        }
        --right;

        for (size_t i = right; i >= left; --i) {
            ++s.comparison_count;
            if (vec[i - 1] > vec[i])
            {
                swap(vec[i - 1], vec[i]);
                s.copy_count += 3;
            }
        }
        ++left;
    }

    return s;
}

template <class T>
stats quick_sort(std::vector<T>& vec)
{
    stats s;

    quick_sort(vec, 0, vec.size(), s);

    return s;

}

template <class T>
void part_quick_sort(vector<T>& vec, size_t start, size_t end, stats& s)
{
    T pivot = vec[(start + end) / 2];
    while (start <= end)
    {
        while (vec[start] < pivot)
        {
            ++start;
            ++s.comparison_count;
        }
        while (vec[end] > pivot)
        {
            --end;
            ++s.comparison_count;
        }
        if (start <= end)
        {
            swap(vec[start], vec[end]);
            ++start;
            --end;
            s.copy_count += 3;
        }
    }
    return start;
}

template <class T>
void quick_sort(std::vector<T>& vec, size_t start, size_t end, stats& s)
{
    if (start >= end)
    {
        return;
    }
    size_t right_start = part_quick_sort(vec, start, end, s);
    quick_sort(vec, start, right_start - 1, s);
    quick_sort(vec, right_start, end, s);
}
