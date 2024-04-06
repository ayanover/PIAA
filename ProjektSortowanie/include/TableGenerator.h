//
// Created by rexiv on 18.03.2024.
//

#ifndef SORTING_ALGORITHMS_TABLEGENERATOR_H
#define SORTING_ALGORITHMS_TABLEGENERATOR_H

#include <vector>
#include <cstdlib> // for rand and srand
#include <ctime> // for time
#include <algorithm>
std::vector<int> generateRandomVector(long size, float percent) {
    std::srand(std::time(nullptr));
    std::vector<int> vec;
    for(int i = 0; i < size; i++) {
        vec.push_back(std::rand());
    }
    int pivot = (percent/100 * size);
    std::sort(vec.begin(), vec.begin() + pivot);
    return vec;
}
#endif //SORTING_ALGORITHMS_TABLEGENERATOR_H
