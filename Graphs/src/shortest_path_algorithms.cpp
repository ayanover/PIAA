#include "../include/graphs/shortest_path_algorithms.hpp"
#include "../include/graphs/graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>


void dijkstra(Graph &graph, int sourceIndex, ShortestPathResult &result)
{
    const int INF = std::numeric_limits<int>::max();

    int V = graph.vertices().size();
    result.clear();

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, sourceIndex});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int uDist = pq.top().first;
        pq.pop();

        if (result.find(u) != result.end())
            continue;

        result[u] = {uDist, {}};

        std::vector<int> neighbors = graph.incidentEdges(u);
        for (int v : neighbors)
           {
            std::vector<int> endVertices = graph.endVertices(v);
            int oppositeVertex = (u == endVertices[0]) ? endVertices[1] : endVertices[0];
            int edgeWeight = graph.getEdgeWeight(u, oppositeVertex);

               if (result.find(oppositeVertex) == result.end() || uDist + edgeWeight < result[oppositeVertex].first)
               {
                   result[oppositeVertex] = {uDist + edgeWeight, result[u].second}; // Update path to include the path from source to u
                   result[oppositeVertex].second.push_back(u); // Append u to the path
                   pq.push({uDist + edgeWeight, oppositeVertex});
               }
               else if (uDist + edgeWeight == result[oppositeVertex].first)
               {
                   result[oppositeVertex].second.push_back(u);
               }

           }
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int V = graph.V;
    int E = graph.E;
    result.distance.resize(V, numeric_limits<int>::max()); // Initialize distances to infinity
    result.predecessor.resize(V, -1); // Initialize predecessors to -1
    result.distance[sourceIndex] = 0; // Distance to source vertex is 0

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = graph.edges[j].source;
            int v = graph.edges[j].destination;
            int weight = graph.edges[j].weight;
            if (result.getEdgeWeight[u] != numeric_limits<int>::max() && result.distance[u] + weight < result.distance[v]) {
                result.distance[v] = result.distance[u] + weight;
                result.predecessor[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; ++i) {
        int u = graph.edges[i].source;
        int v = graph.edges[i].destination;
        int weight = graph.edges[i].weight;
        if (result.distance[u] != numeric_limits<int>::max() && result.distance[u] + weight < result.distance[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }
    return true;
}
