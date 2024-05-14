#include <iostream>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include <random>
#include <chrono>
#include "adjacency_list_graph.cpp"
#include "shortest_path_algorithms.cpp"
#include "../include/graphs/adjacency_list_graph.hpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
#include "../include/graphs/random_graph_generator.hpp"

double average(double arr[], long size) {
    double sum = 0.0;

    for (int i = 0; i < 1; ++i) {
        sum += arr[i];
    }

    double average = sum / size;
    return average;
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
    std::vector<double> dijkstraListMeasurements;
    std::vector<double> dijkstraMatrixMeasurements;
    std::vector<double> bellmanListMeasurements;
    std::vector<double> bellmanMatrixMeasurements;
    ShortestPathResult resultDijkstra;
    ShortestPathResult resultBellman;
    const int ITERATIONS = 1;
    int num_elements[] = {10, 50, 100, 500, 1000};
    int fill_percent[] = {25, 50, 75, 100};
    for(int fill : fill_percent){
        for(int num : num_elements){
            std::vector<double> measurements;
            double dijkstraList[ITERATIONS];
            double dijkstraMatrix[ITERATIONS];
            double bellmanList[ITERATIONS];
            double bellmanMatrix[ITERATIONS];
            for(int i=0; i< ITERATIONS; i++){
                std::unique_ptr<AdjacencyListGraph> graphList(new AdjacencyListGraph(num));
                std::unique_ptr<AdjacencyListGraph> graphMatrix(new AdjacencyListGraph(num));
                RandomGraphGenerator::generateRandomGraph(*graphList, num , fill);
                RandomGraphGenerator::generateRandomGraph(*graphMatrix, num , fill);

                auto start = std::chrono::high_resolution_clock::now();
                dijkstra(*graphList, 0 , resultDijkstra);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationDijkstraList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                dijkstraList[i] = durationDijkstraList.count();

                start = std::chrono::high_resolution_clock::now();
                dijkstra(*graphMatrix, 0 , resultDijkstra);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationDijkstraMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                dijkstraMatrix[i] = durationDijkstraMatrix.count();

                start = std::chrono::high_resolution_clock::now();
                bellmanFord(*graphList, 0 , resultDijkstra);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationBellmanList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                bellmanList[i] = durationBellmanList.count();

                start = std::chrono::high_resolution_clock::now();
                bellmanFord(*graphMatrix, 0 , resultDijkstra);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationBellmanMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                bellmanMatrix[i] = durationBellmanMatrix.count();
            }

            measurements.push_back(average(dijkstraList, sizeof(dijkstraList)-1));
            measurements.push_back(average(dijkstraMatrix, sizeof(dijkstraMatrix)-1));
            measurements.push_back(average(bellmanList, sizeof(bellmanList)-1));
            measurements.push_back(average(bellmanMatrix, sizeof(bellmanMatrix)-1));

            dijkstraListMeasurements.push_back(average(dijkstraList, sizeof(dijkstraList)-1));
            dijkstraMatrixMeasurements.push_back(average(dijkstraMatrix, sizeof(dijkstraMatrix)-1));
            bellmanListMeasurements.push_back(average(bellmanList, sizeof(bellmanList)-1));
            bellmanMatrixMeasurements.push_back(average(bellmanMatrix, sizeof(bellmanMatrix)-1));
            std::cout<< measurements[0] * 1000 << " " << measurements[1] * 1000 << " " << measurements[2] * 1000 << " " << measurements[3]*1000 << std::endl;
            //std::cout<< dijkstraListMeasurements[1] * 1000 << " " << dijkstraMatrixMeasurements[0] * 1000 << " " << bellmanListMeasurements[0] * 1000 << std::endl;
            //std::cout<< dijkstraListMeasurements[2] * 1000 << std::endl;
            //std::cout<< dijkstraListMeasurements[3] * 1000 << std::endl;
        }


        SaveMeasurementsToFile(dijkstraListMeasurements, std::to_string(fill)+"_dijkstraList.txt");
        SaveMeasurementsToFile(dijkstraMatrixMeasurements, std::to_string(fill)+"_dijkstraMatrix.txt");
        SaveMeasurementsToFile(bellmanListMeasurements, std::to_string(fill)+"_bellmanList.txt");
        SaveMeasurementsToFile(bellmanMatrixMeasurements, std::to_string(fill)+"_bellmanMatrix.txt");

        dijkstraListMeasurements.clear();
        dijkstraMatrixMeasurements.clear();
        bellmanListMeasurements.clear();
        bellmanMatrixMeasurements.clear();
    }


    return 0;
}


