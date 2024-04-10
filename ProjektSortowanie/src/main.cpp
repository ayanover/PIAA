#include "algorithms/quicksort.h"
#include "algorithms/introsort.h"
#include "algorithms/mergesort.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <sstream>
#include "../include/TableGenerator.h"
using namespace std::string_literals;

bool CheckCorrectSorting(std::vector<int> arr, std::vector<int> sortedArr){
    std::sort(arr.begin(), arr.end());
    if(arr == sortedArr){
        return true;
    }
    else{
        return false;
    }
}
std::vector<int> getTestData(long size, float percentSolved, bool isReversed)
{
    if(isReversed){
        std::vector data = generateRandomVector(size, percentSolved);
        std::reverse(data.begin(), data.end());
        return data;
    }
    else{
        return generateRandomVector(size, percentSolved);
    }
}

void UpdateProgress(short iteration){
    std::system("cls");
    std::cout << "Measurements in progress..." << std::endl;
    std::cout << iteration << " / 100";
}

double average(double arr[], long size) {
    double sum = 0.0;

    for (int i = 0; i < 100; ++i) {
        sum += arr[i];
    }

    double average = sum / size;
    return average;
}

std::vector<double> getAverageTimes(long size, float percentSolved, bool isReversed)
{
    QuickSort<int> quickSort;
    MergeSort<int> mergeSort;
    IntroSort<int> introSort;
    double quicksort_measurements[100];
    double mergesort_measurements[100];
    double introsort_measurements[100];
    for(int i=0; i<100; i++){
        auto unsortedData = getTestData(size, percentSolved, isReversed);

        //UpdateProgress(i+1);

        // quickSort
        auto data = unsortedData;

        auto start = std::chrono::high_resolution_clock::now();
        quickSort.sort(data.begin(), data.end());
        auto end = std::chrono::high_resolution_clock::now();
        if(!CheckCorrectSorting(unsortedData, data)){
            std::cout << "Sorting Unsuccessful! Aborting..." << std::endl;
        };
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        quicksort_measurements[i] = duration.count();

        // mergeSort
        data = unsortedData;

        start = std::chrono::high_resolution_clock::now();
        mergeSort.sort(data.begin(), data.end());
        end = std::chrono::high_resolution_clock::now();
        if(!CheckCorrectSorting(unsortedData, data)){
            std::cout << "Sorting Unsuccessful! Aborting..." << std::endl;;
        };

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        mergesort_measurements[i] = duration.count();

        // introSort
        data = unsortedData;

        start = std::chrono::high_resolution_clock::now();
        introSort.sort(data.begin(), data.end());
        end = std::chrono::high_resolution_clock::now();
        if(!CheckCorrectSorting(unsortedData, data)){
            std::cout << "Sorting Unsuccessful! Aborting..." << std::endl;;
        };

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        introsort_measurements[i] = duration.count();
    }

    std::vector<double> measurements;
    measurements.push_back(average(quicksort_measurements, sizeof(quicksort_measurements)-1));
    measurements.push_back(average(mergesort_measurements, sizeof(mergesort_measurements)-1));
    measurements.push_back(average(introsort_measurements, sizeof(introsort_measurements)-1));
    std::cout<< measurements[0] * 1000 << " " << measurements[1] * 1000 << " " << measurements[2] * 1000 << std::endl;
    return measurements;
}

void SaveMeasurementsToFile(std::vector<double> data, std::string filename){
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (int i = 0; i < data.size(); i++) {
            outputFile << data[i] * 1000 << "\n";
        }
        outputFile.close();
        std::cout << "Measurements saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

int main(int argc, char* argv[])
{
    long VECTOR_SIZES[] = {10000, 50000, 100000, 500000, 1000000};
    float PERCENT_SOLVED[] = { 0,25, 50, 75, 95, 99, 99.7};
    std::vector<double> quicksortMeasurements;
    std::vector<double> mergesortMeasurements;
    std::vector<double> introsortMeasurements;

    for(long size : VECTOR_SIZES){

        for(float percent : PERCENT_SOLVED){
            std::vector<double> measurements = getAverageTimes(size, percent, false);

            quicksortMeasurements.push_back(measurements[0]);
            mergesortMeasurements.push_back(measurements[1]);
            introsortMeasurements.push_back(measurements[2]);
        }
        std::vector<double> measurements = getAverageTimes(size, 100, true);

        quicksortMeasurements.push_back(measurements[0]);
        mergesortMeasurements.push_back(measurements[1]);
        introsortMeasurements.push_back(measurements[2]);

        SaveMeasurementsToFile(quicksortMeasurements, std::to_string(size)+"_quicksort.txt");
        SaveMeasurementsToFile(mergesortMeasurements, std::to_string(size)+"_mergesort.txt");
        SaveMeasurementsToFile(introsortMeasurements, std::to_string(size)+"_introsort.txt");

        quicksortMeasurements.clear();
        mergesortMeasurements.clear();
        introsortMeasurements.clear();
    }


    return 0;
}
