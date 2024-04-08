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

        while (left < middle && right < end) {
            if (*left < *right) {
                *tempIt++ = std::move(*left++);
            } else {
                *tempIt++ = std::move(*right++);
            }
        }

        while (left < middle) {
            *tempIt++ = std::move(*left++);
        }
        while (right < end) {
            *tempIt++ = std::move(*right++);
        }

        std::move(temp.begin(), temp.end(), start);
    }
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
