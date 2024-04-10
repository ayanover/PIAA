#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include <vector>

// sortowanie przez kopcowanie. Należy samodzielnie zaimplementować odpowiedni kopiec, który kopcuje bez użycia dodatkowej pamięci.

template <typename T>
class HeapSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int n = end - start;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(start, end, i);

        for (int i = n - 1; i > 0; i--) {
            std::swap(*(start), *(start + i));

            heapify(start, start + i, 0);
        }
    };
private:
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
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H
