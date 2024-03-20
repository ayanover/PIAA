//
// Created by rexiv on 18.03.2024.
//

#ifndef SORTING_ALGORITHMS_TABLEGENERATOR_H
#define SORTING_ALGORITHMS_TABLEGENERATOR_H

#include <vector>
#include <cstdlib> // for rand and srand
#include <ctime> // for time

std::vector<int> generateRandomVector(int n) {
    std::srand(std::time(nullptr));
    std::vector<int> vec(n);
    for(int i = 0; i < n; i++) {
        vec[i] = std::rand();
    }
    return vec;
}
#endif //SORTING_ALGORITHMS_TABLEGENERATOR_H
