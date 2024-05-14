//
// Created by rexiv on 13.05.2024.
//
#include <iostream>
#include <fstream>
#include <memory>
#include "../include/graphs/graph.hpp"
#include "../include/graphs/shortest_path_algorithms.hpp"
#include "../include/graphs/adjacency_list_graph.hpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) {}
void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result){}
void drawImplementationMenu(){
    int choice, algorithmChoice;
    std::cout<< "What implementation would you like to test?" << std::endl << std::endl;
    std::cout<< "1.Adjacency List Graph" << std::endl;
    std::cout<< "2.Adjacency Matrix Graph" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
        case 2:
            system("cls");
            std::cout<< "What implementation would you like to test?" << std::endl << std::endl;
            std::cout<< "1.Dijkstra" << std::endl;
            std::cout<< "2.Bellman Ford" << std::endl;
            std::cin >> algorithmChoice;
            break;
        default:
            std::cout<<"Wrong Choice" << std::endl;
            break;
    }
}

void ExecuteAlgorithm(int algorithm, int graphOfChoice){
    std::unique_ptr<Graph> graph;
    ShortestPathResult result;
    std::ifstream graphFile("../sp_data/graph/graphV10D0.5.txt");
    if (!graphFile)
    {
        std::cerr << "Error: Unable to open graph data file." << std::endl;
        return;
    }

    switch(graphOfChoice){
        case 1:
            graph = AdjacencyListGraph::createGraph(graphFile);
            break;
        case 2:
            graph = AdjacencyMatrixGraph::createGraph(graphFile);
            break;
        default:
            return;
    }
    graphFile.close();

    switch(algorithm){
        case 1:
            dijkstra(*graph, 7 , result);
            break;
        case 2:
            bellmanFord(*graph, 7 , result);
    }

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

}

int main(){
    drawImplementationMenu();

    return 0;
}