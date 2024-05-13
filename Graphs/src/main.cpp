#include <iostream>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include "adjacency_list_graph.cpp"
#include "shortest_path_algorithms.cpp"
#include "../include/graphs/adjacency_list_graph.hpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"

using ShortestPathResult = std::map<int, std::pair<int, std::vector<int>>>;

std::unordered_map<int, std::vector<std::pair<int, int>>> generate_weighted_adjacency_list(int num_elements, int fill_percent) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency_list;

    // Calculate the number of edges based on fill percentage
    int num_edges = (num_elements * (num_elements - 1) / 2) * (fill_percent / 100);

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Generate random edges with weights
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    for (int i = 0; i < num_elements; ++i) {
        for (int j = i + 1; j < num_elements; ++j) {
            edges.push_back({i, {j, std::rand() % 100 + 1}});  // random weights between 1 and 100
        }
    }

    // Shuffle the edges vector
    std::random_shuffle(edges.begin(), edges.end());

    // Add edges to the adjacency list
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second.first;
        int weight = edge.second.second;
        adjacency_list[u].push_back({v, weight});
        adjacency_list[v].push_back({u, weight});
        if (adjacency_list[u].size() >= num_elements - 1) break;  // Ensure each node has at most (num_elements - 1) edges
    }

    return adjacency_list;
}

int main(int argc, char* argv[])
{
    std::ifstream graphFile("../sp_data/graph/graphV10D0.5.txt");
    if (!graphFile)
    {
        std::cerr << "Error: Unable to open graph data file." << std::endl;
        return 1;
    }

    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(graphFile);
    //std::unique_ptr<Graph> graph = AdjacencyMatrixGraph::createGraph(graphFile);
    graphFile.close();
    ShortestPathResult resultDijkstra;
    ShortestPathResult resultBellman;

    dijkstra(*graph, 7 , resultDijkstra);


    for (const auto& [vertexIndex, value] : resultDijkstra)
    {
        std::cout << "Shortest path to vertex " << vertexIndex << " is " << value.first << std::endl;
        std::cout << "Path: ";
        for (int v : value.second)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}


