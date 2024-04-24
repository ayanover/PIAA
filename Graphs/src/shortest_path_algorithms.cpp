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
                result[oppositeVertex] = {uDist + edgeWeight, {u}};
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
    // TODO: implement
    return true;
}
