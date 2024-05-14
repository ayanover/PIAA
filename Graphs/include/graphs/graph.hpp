#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>
#include <memory>

class Graph
{
protected:
    int V;

public:
    struct Edge {
        int src;
        int dest;
        int weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };
    explicit Graph(int vertices) : V(vertices) {}

    virtual void addEdge(int v1, int v2, int weight) = 0;

    virtual int getEdgeWeight(int v1, int v2) = 0;

    virtual std::vector<int> endVertices(int e) = 0;

    virtual int opposite(int v, int e) = 0;

    virtual bool areAdjacent(int v, int w) = 0;

    virtual void replace(int v, int x) = 0;

    virtual void insertVertex(int o) = 0;

    virtual void insertEdge(int v, int w, int o) = 0;

    virtual void removeVertex(int v) = 0;

    virtual void removeEdge(int v1, int v2) = 0;

    virtual std::vector<std::pair<int, int>> incidentEdges(int v) = 0;

    virtual std::vector<int> vertices() = 0;

    virtual std::vector<std::vector<int>> edges(bool isBuilding) = 0;

};

#endif /* GRAPH_HPP_ */
