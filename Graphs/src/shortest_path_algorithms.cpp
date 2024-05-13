#include "../include/graphs/shortest_path_algorithms.hpp"
#include "../include/graphs/graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include <algorithm>
#include <unordered_set>


const int INF = std::numeric_limits<int>::max();

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    std::unordered_set<int> visited;

    int V = graph.vertices().size();

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, sourceIndex});

    while (!pq.empty()) {
        int u = pq.top().second;
        int uDist = pq.top().first;
        pq.pop();

        if (visited.find(u) != visited.end())
            continue;

        visited.insert(u);

        result[u].first = uDist;
        result[result[u].second].second.push_back(u);

        std::vector<int> neighbors = graph.incidentEdges(u);
        for (int v : neighbors) {
            std::vector<int> endVertices = graph.endVertices(v);
            int oppositeVertex = (u == endVertices[0]) ? endVertices[1] : endVertices[0];
            int edgeWeight = graph.getEdgeWeight(u, oppositeVertex);

            if (visited.find(oppositeVertex) == visited.end() || uDist + edgeWeight < result[oppositeVertex].first) {
                result[oppositeVertex] = {uDist + edgeWeight, result[u].second}; // Update path to include the path from source to u
                result[oppositeVertex].second.emplace_back(oppositeVertex); // Append u to the path
                result = result;
                pq.push({uDist + edgeWeight, oppositeVertex});
            }
        }
    }
    result = result;
}

bool bellmanFord(Graph& graph, int source, ShortestPathResult& result)
{
    const int INF = std::numeric_limits<int>::max();
    int V = graph.vertices().size();
    std::vector<int> distance(V, INF);
    distance[source] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            std::vector<int> adjacentEdges = graph.incidentEdges(u);
            for (int e : adjacentEdges) {
                auto endpoints = graph.endVertices(e);
                int v = (endpoints[0] == u) ? endpoints[1] : endpoints[0];
                int weight = graph.getEdgeWeight(u, v);
                if (distance[u] != INF && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < V; ++u) {
        std::vector<int> adjacentEdges = graph.incidentEdges(u);
        for (int e : adjacentEdges) {
            auto endpoints = graph.endVertices(e);
            int v = (endpoints[0] == u) ? endpoints[1] : endpoints[0];
            int weight = graph.getEdgeWeight(u, v);
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                // Negative weight cycle detected
                throw std::runtime_error("Graph contains a negative weight cycle");
            }
        }
    }

    // Store shortest paths in result variable
    for (int i = 0; i < V; ++i) {
        if (i != source && distance[i] != INF) {
            std::vector<int> path;
            int current = i;
            while (current != source) {
                path.push_back(current);
                std::vector<int> adjacentEdges = graph.incidentEdges(current);
                for (int e : adjacentEdges) {
                    auto endpoints = graph.endVertices(e);
                    int v = (endpoints[0] == current) ? endpoints[1] : endpoints[0];
                    int weight = graph.getEdgeWeight(current, v);
                    if (distance[current] == distance[v] + weight) {
                        current = v;
                        break;
                    }
                }
            }
            path.push_back(source);
            std::reverse(path.begin(), path.end());
            result[i] = std::make_pair(distance[i], path);
        }
    }
}
