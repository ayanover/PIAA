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

    void heapSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        int n = end - start;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(start, end, i);

        for (int i = n - 1; i > 0; i--) {
            std::swap(*(start), *(start + i));

            heapify(start, start + i, 0);
        }
    }

    void heapify(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        auto n = end - start;

        if (left < n && *(start + left) > *(start + largest))
            largest = left;

        if (right < n && *(start + right) > *(start + largest))
            largest = right;

        if (largest != i) {
            std::swap(*(start + i), *(start + largest));
            heapify(start, end, largest);
        }
    }

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
        auto pivot = *start;
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
            heapSort(start, end);
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
        int depthLimit = 2 * std::log(end - start);
        introsort(start, end, depthLimit);
    }
};
#endif //SORTING_ALGORITHMS_INTROSORT_H
