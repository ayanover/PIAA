#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T>
class IntroSort
{
private:
    static const int INSERTION_SORT_THRESHOLD = 16;

    void insertionSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        for (auto i = start + 1; i != end; ++i)
        {
            T key = std::move(*i);
            auto j = i - 1;
            while (j >= start && key < *j)
            {
                *(j + 1) = std::move(*j);
                --j;
            }
            *(j + 1) = std::move(key);
        }
    }

    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start,
                                                typename std::vector<T>::iterator end)
    {
        auto pivot = *start; // Choose the first element as the pivot
        auto i = start - 1;
        auto j = end;

        while (true)
        {
            do
            {
                ++i;
            } while (*i < pivot);

            do
            {
                --j;
            } while (*j > pivot);

            if (i >= j)
            {
                return j;
            }

            std::iter_swap(i, j);
        }
    }

    void introsort(typename std::vector<T>::iterator start,
                   typename std::vector<T>::iterator end,
                   int depthLimit)
    {
        if (end - start <= INSERTION_SORT_THRESHOLD)
        {
            insertionSort(start, end);
            return;
        }

        if (depthLimit == 0)
        {
            std::make_heap(start, end);
            std::sort_heap(start, end);
            return;
        }

        if (start < end)
        {
            auto pivot = partition(start, end);
            introsort(start, pivot + 1, depthLimit - 1);
            introsort(pivot + 1, end, depthLimit - 1);
        }
    }

public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int depthLimit = 2 * std::log(end - start); // Depth limit for quicksort recursion
        introsort(start, end, depthLimit);
    }
};
#endif //SORTING_ALGORITHMS_INTROSORT_H
