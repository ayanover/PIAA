#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <iostream>
template <typename T>
class QuickSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (start < end)
        {
            typename std::vector<T>::iterator pivotIndex = partition(start, end);

            sort(start, pivotIndex);
            sort(pivotIndex + 1, end);
        }
    }

private:
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        typename std::vector<T>::iterator pivot = start;
        std::cout<<*pivot << std::endl;

        typename std::vector<T>::iterator left = start + 1;
        typename std::vector<T>::iterator right = end;

        while (left <= right)
        {
            while (*right > *pivot)
            {
                right--;
            }
            while (*left <= *pivot){
                left++;
            }
            if (left < right)
            {
                std::iter_swap(left, right);
            }
            else
            {
                std::iter_swap(pivot, right);
                return right;
            }

        }
        return left;
    }
};

#endif //SORTING_ALGORITHMS_QUICKSORT_H
