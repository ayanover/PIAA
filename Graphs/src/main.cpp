#include <iostream>
#include <fstream>
#include "adjacency_list_graph.cpp"
#include "shortest_path_algorithms.cpp"
#include "../include/graphs/adjacency_list_graph.hpp"

using ShortestPathResult = std::map<int, std::pair<int, std::vector<int>>>;

int main(int argc, char* argv[])
{
    std::ifstream graphFile("../sp_data/graph/graphV10D0.5.txt");
    if (!graphFile)
    {
        std::cerr << "Error: Unable to open graph data file." << std::endl;
        return 1;
    }

    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(graphFile);
    graphFile.close();
    ShortestPathResult result;

    dijkstra(*graph, 0 , result);

    for (const auto& [vertexIndex, value] : result)
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
