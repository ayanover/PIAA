#ifndef SORTING_ALGORITHMS_INSERTSORT_H
#define SORTING_ALGORITHMS_INSERTSORT_H
#include <vector>

// sortowanie przez wstawianie

template <typename T>
class InsertSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
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
    };
};

#endif //SORTING_ALGORITHMS_INSERTSORT_H
