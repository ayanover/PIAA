#ifndef GRAPH_ALGORITHMS_RANDOM_GRAPH_GENERATOR_HPP
#define GRAPH_ALGORITHMS_RANDOM_GRAPH_GENERATOR_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Graph.hpp"

class RandomGraphGenerator {
public:
    static void generateRandomGraph(Graph& graph, int numVertices, double fillPercentage) {
        srand(time(nullptr));

        int maxEdges = static_cast<int>((fillPercentage / 100.0) * (numVertices * (numVertices - 1) / 2));

        while (graph.edges(true).size() < maxEdges) {
            int v1 = rand() % numVertices;
            int v2 = rand() % numVertices;

            if (v1 != v2 && !graph.areAdjacent(v1, v2)) {
                int weight = rand() % 100 + 1;
                graph.addEdge(v1, v2, weight);
            }
        }
    }
};




#endif //GRAPH_ALGORITHMS_RANDOM_GRAPH_GENERATOR_HPP
