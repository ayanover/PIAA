#ifndef SORTING_ALGORITHMS_SHELLSORT_H
#define SORTING_ALGORITHMS_SHELLSORT_H
#include <vector>

// sortowanie Shella

template <typename T>
class ShellSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int n = std::distance(start, end);
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = *(start + i);
                int j;
                for (j = i; j >= gap && *(start + j - gap) > temp; j -= gap) {
                    *(start + j) = *(start + j - gap);
                }
                *(start + j) = temp;
            }
        }
    }
};

#endif //SORTING_ALGORITHMS_SHELLSORT_H
