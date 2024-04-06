#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (std::distance(start, end) <= 1) {
            return;
        }

        auto middle = start + std::distance(start, end) / 2;

        sort(start, middle);
        sort(middle, end);

        merge(start, middle, end);
    }

private:
    void merge(typename std::vector<T>::iterator start,
               typename std::vector<T>::iterator middle,
               typename std::vector<T>::iterator end)
    {
        std::vector<T> temp(std::distance(start, end));
        auto left = start;
        auto right = middle;
        auto tempIt = temp.begin();

        // Merge the two halves into temp
        while (left < middle && right < end) {
            if (*left < *right) {
                *tempIt++ = std::move(*left++);
            } else {
                *tempIt++ = std::move(*right++);
            }
        }

        // Copy the remaining elements from left or right half, if any
        while (left < middle) {
            *tempIt++ = std::move(*left++);
        }
        while (right < end) {
            *tempIt++ = std::move(*right++);
        }

        // Copy the merged elements from temp back to the original range
        std::move(temp.begin(), temp.end(), start);
    }
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
