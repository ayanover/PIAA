#include "../include/graphs/adjacency_list_graph.hpp"

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{

    int V, E;
    is >> V >> E;

    std::unique_ptr<AdjacencyListGraph> graph = std::make_unique<AdjacencyListGraph>(V);

    int v1, v2, weight;
    for (int i = 0; i < E; ++i)
    {
        is >> v1 >> v2 >> weight;
        graph->insertEdge(v1, v2, weight);
    }

    return std::move(graph);
    //return std::make_unique<AdjacencyListGraph>();
}
