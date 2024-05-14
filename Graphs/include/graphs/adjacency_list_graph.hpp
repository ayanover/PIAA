#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include "Graph.hpp"

class AdjacencyListGraph : public Graph {
private:
    struct Edge {
        int src;
        int dest;
        int weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };

    std::vector<std::vector<Edge>> adjList;
    std::vector<int> elements;

public:
    explicit AdjacencyListGraph(int vertices) : Graph(vertices) {
        adjList.resize(vertices);
        elements.resize(vertices);
    }

    void addEdge(int v1, int v2, int weight) override {
        adjList[v1].emplace_back(v1, v2, weight);
    }

    int getEdgeWeight(int v1, int v2) override {
        for (const Edge &edge : adjList[v1]) {
            if (edge.dest == v2) {
                return edge.weight;
            }
        }
        return -1; // If there's no edge from v1 to v2
    }

    std::vector<int> endVertices(int e) override {
        if (e >= adjList.size() || adjList[e].empty())
            return {-1, -1};

        return {adjList[e][0].src, adjList[e][0].dest};
    }

    int opposite(int v, int e) override {
        if (adjList[v].empty())
            return -1;

        for (const Edge &edge : adjList[v]) {
            if (edge.dest == e) {
                return edge.src;
            }
        }
        return -1;
    }

    bool areAdjacent(int v, int w) override {
        for (const Edge &edge : adjList[v]) {
            if (edge.dest == w)
                return true;
        }
        return false;
    }

    void replace(int v, int x) override {
        if (v < elements.size())
            elements[v] = x;
    }

    void insertVertex(int o) override {
        adjList.emplace_back(std::vector<Edge>());
        elements.push_back(o);
        V++;
    }

    void insertEdge(int v, int w, int o) override {
        if (v >= V || w >= V)
            return;

        adjList[v].emplace_back(v, w, o);
    }

    void removeVertex(int v) override {
        if (v >= V)
            return;

        for (int i = 0; i < adjList.size(); ++i) {
            auto it = std::remove_if(adjList[i].begin(), adjList[i].end(), [v](const Edge &edge) { return edge.dest == v; });
            adjList[i].erase(it, adjList[i].end());
        }

        adjList.erase(adjList.begin() + v);
        elements.erase(elements.begin() + v);
        V--;
    }

    void removeEdge(int v1, int v2) override {
        adjList[v1].erase(std::remove_if(adjList[v1].begin(), adjList[v1].end(),
                                         [v2](const Edge &edge) { return edge.dest == v2; }),
                          adjList[v1].end());
    }

    std::vector<std::pair<int, int>> incidentEdges(int v) override {
        if (v >= V) {
            throw std::out_of_range("Vertex index out of range");
        }

        std::vector<std::pair<int, int>> result;
        for (const Edge& edge : adjList[v]) {
            result.push_back(std::make_pair((edge.dest), (edge.weight)));
        }
        return result;
    }

    std::vector<int> vertices() override {
        std::vector<int> result;
        for (int i = 0; i < V; ++i)
            result.push_back(i);
        return result;
    }

    std::vector<std::vector<int>> edges(bool isBuilding) override {
        std::vector<std::vector<int>> res;
        for (int i = 0; i < V; ++i) {
            for (const Edge &edge : adjList[i]) {
                if(!isBuilding){
                    res[i].push_back(edge.src);
                }
                res[i].push_back(edge.dest);
                res[i].push_back(edge.weight);
            }
        }
        return res;
    }

    static std::unique_ptr<Graph> createGraph(std::istream &is) {
        int V, E;
        is >> V >> E;

        std::unique_ptr<AdjacencyListGraph> graph = std::make_unique<AdjacencyListGraph>(V);

        int v1, v2, weight;
        for (int i = 0; i < E; ++i) {
            is >> v1 >> v2 >> weight;
            graph->insertEdge(v1, v2, weight);
        }

        return std::move(graph);
    };
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
