#include <iostream>
#include "../include/algorithms/quicksort.h"
#include <vector>
#include "TableGenerator.h"
using namespace std::string_literals;

std::vector<int> getTestData()
{
    return generateRandomVector(1000000);
}

int main(int argc, char* argv[])
{
    auto data = getTestData();

    QuickSort<int> quickSort;
    quickSort.sort(data.begin(),data.end());
    std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec) {
        for (auto& el : vec) {
            os << el << ' ';
        }
        return os;
    }
    return 0;
}
