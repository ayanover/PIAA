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
    int V = graph.vertices().size();
    std::unordered_set<int> visited;
    for (int i = 0; i < V; ++i) {
        result[i] = {std::numeric_limits<int>::max(), std::vector<int>()};
    }
    // Custom comparison function for the priority queue
    auto compare = [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.first > rhs.first; // Compare based on distance
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);

    pq.push({0, sourceIndex});
    result[sourceIndex] = {0, std::vector<int>{sourceIndex}}; // Distance from source to itself is 0, and path is empty

    while (!pq.empty()) {
        int u = pq.top().second;
        int uDist = pq.top().first;
        pq.pop();

        if (visited.find(u) != visited.end())
            continue;

        visited.insert(u);

        std::vector<std::pair<int, int>> neighbors = graph.incidentEdges(u);
        for (const auto& v : neighbors) {
            int edgeWeight = graph.getEdgeWeight(u, v.first);

            if ((uDist + edgeWeight) < result[v.first].first) {
                result[v.first].first = uDist + edgeWeight; // Update shortest distance
                result[v.first].second = result[u].second; // Update shortest path
                result[v.first].second.push_back(v.first); // Append v to the path

                pq.push({result[v.first].first, v.first}); // Push the updated distance and vertex to the priority queue
            }
        }
    }
}




bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    int V = graph.vertices().size();
    std::vector<int> distance(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    distance[sourceIndex] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (const auto& neighbor : graph.incidentEdges(u)) {
                int v = neighbor.first;
                int weightUV = neighbor.second;

                if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weightUV < distance[v]) {
                    distance[v] = distance[u] + weightUV;
                    parent[v] = u;
                }
            }
        }
    }

    //czy istnieją ujemne cykle
    for (int u = 0; u < V; ++u) {
        for (const auto& neighbor : graph.incidentEdges(u)) {
            int v = neighbor.first;
            int weightUV = neighbor.second;

            if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weightUV < distance[v]) {
                return false;
            }
        }
    }

    // Zapisz odległości i ścieżki w wynikach
    for (int i = 0; i < V; ++i) {
        std::vector<int> path;
        int current = i;
        while (current != -1) {
            path.insert(path.begin(), current);
            current = parent[current];
        }
        result[i] = {distance[i], path};
    }

    return true;
}