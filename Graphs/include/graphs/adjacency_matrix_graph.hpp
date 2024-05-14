#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Graph.hpp"

class AdjacencyMatrixGraph : public Graph {
private:
    struct Edge {
        int src;
        int dest;
        int weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };

    std::vector<Edge> Edges;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    explicit AdjacencyMatrixGraph(int vertices) : Graph(vertices) {
        adjacencyMatrix.resize(V, std::vector<int>(V, 0));
    }

    void addEdge(int v1, int v2, int weight) override {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacencyMatrix[v1][v2] = weight;
        adjacencyMatrix[v2][v1] = weight;
        Edges.emplace_back(v1, v2, weight);
    }

    int getEdgeWeight(int v1, int v2) override {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        return adjacencyMatrix[v1][v2];
    }

    std::vector<int> endVertices(int e) override {
        if (e >= Edges.size() || e < 0) {
            throw std::out_of_range("Edge index out of range");
        }
        return {Edges[e].src, Edges[e].dest};
    }

    int opposite(int v, int e) override {
        if (e >= Edges.size() || e < 0) {
            throw std::out_of_range("Edge index out of range");
        }
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        if (Edges[e].src == v) {
            return Edges[e].dest;
        } else if (Edges[e].dest == v) {
            return Edges[e].src;
        } else {
            throw std::invalid_argument("Vertex and edge are not incident");
        }
    }

    bool areAdjacent(int v, int w) override {
        if (v >= V || w >= V || v < 0 || w < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        return adjacencyMatrix[v][w] != 0;
    }

    void replace(int v, int x) override {
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
    }

    void insertVertex(int o) override {
        ++V;
        adjacencyMatrix.resize(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; ++i) {
            adjacencyMatrix[i].resize(V, 0);
        }
    }

    void insertEdge(int v, int w, int o) override {
        addEdge(v, w, o);
    }

    void removeVertex(int v) override {
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacencyMatrix.erase(adjacencyMatrix.begin() + v);
        for (auto &row : adjacencyMatrix) {
            row.erase(row.begin() + v);
        }
        // Remove Edges connected to the vertex being removed
        Edges.erase(std::remove_if(Edges.begin(), Edges.end(), [v](const Edge& edge) {
            return edge.src == v || edge.dest == v;
        }), Edges.end());
        --V;
    }

    void removeEdge(int v1, int v2) override {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacencyMatrix[v1][v2] = 0;
        adjacencyMatrix[v2][v1] = 0;
        // Remove the edge from the Edges vector
        Edges.erase(std::remove_if(Edges.begin(), Edges.end(), [v1, v2](const Edge& edge) {
            return (edge.src == v1 && edge.dest == v2) || (edge.src == v2 && edge.dest == v1);
        }), Edges.end());
    }

    std::vector<std::pair<int, int>> incidentEdges(int v) override {
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        std::vector<std::pair<int, int>> incidentEdges;
        for (const auto& edge : Edges) {
            if (edge.src == v) {
                incidentEdges.push_back(std::make_pair(edge.dest, edge.weight));
            } else if (edge.dest == v) {
                incidentEdges.push_back(std::make_pair(edge.src, edge.weight));
            }
        }
        return incidentEdges;
    }

    std::vector<int> vertices() override {
        std::vector<int> vert;
        for (int i = 0; i < V; ++i) {
            vert.push_back(i);
        }
        return vert;
    }

    std::vector<std::vector<int>> edges(bool isBuilding) override {
        std::vector<std::vector<int>> res;
        int i=0;
        for (const auto& edge : Edges) {
            res[i].push_back(edge.src);
            res[i].push_back(edge.dest);
            res[i].push_back(edge.weight);
            i++;
        }
        return res;
    }

    static std::unique_ptr<Graph> createGraph(std::istream &input) {
        int vertices;
        input >> vertices;

        std::unique_ptr<Graph> graph = std::make_unique<AdjacencyMatrixGraph>(vertices);

        int edges;
        input >> edges;

        for (int i = 0; i < edges; ++i) {
            int v1, v2, weight;
            input >> v1 >> v2 >> weight;
            graph->addEdge(v1, v2, weight);
        }

        return graph;
    }
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
