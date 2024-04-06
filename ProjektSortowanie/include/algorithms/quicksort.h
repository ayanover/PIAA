#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class QuickSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (start < end)
        {
            typename std::vector<T>::iterator pivotIndex = partition(start, end);

            if(start < pivotIndex){
                sort(start, pivotIndex);
            }
            if(pivotIndex + 1 < end){
                sort(pivotIndex + 1, end);
            }
        }
    }

private:
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        typename std::vector<T>::iterator pivot = start;
        typename std::vector<T>::iterator left = start + 1;
        typename std::vector<T>::iterator right = end - 1;

        while (left <= right)
        {
            while (left <= right && *right > *pivot)
            {
                right--;
            }
            while (left <= right && *left <= *pivot)
            {
                left++;
            }
            if (left < right)
            {
                std::iter_swap(left, right);
            }
            else
            {
                std::iter_swap(pivot, right);
            }
        }
        return right;
    }
};
#endif //SORTING_ALGORITHMS_QUICKSORT_H