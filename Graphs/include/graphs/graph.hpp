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
    explicit Graph(int vertices) : V(vertices) {}

    // Pure virtual function to add an edge between v1 and v2
    virtual void addEdge(int v1, int v2, int weight) = 0;

    virtual int getEdgeWeight(int v1, int v2) = 0;

    // Pure virtual function to print the adjacency list
    virtual void printAdjList() = 0;

    // Function to get the end vertices of edge e
    virtual std::vector<int> endVertices(int e) = 0;

    // Function to get the opposite vertex of v in edge e
    virtual int opposite(int v, int e) = 0;

    // Function to check if vertices v and w are adjacent
    virtual bool areAdjacent(int v, int w) = 0;

    // Function to replace element in vertex v
    virtual void replace(int v, int x) = 0;

    // Function to replace element in edge e
    virtual void replaceEdge(int e, int x) = 0;

    // Function to insert a vertex with element o
    virtual void insertVertex(int o) = 0;

    // Function to insert an edge (v, w) with element o
    virtual void insertEdge(int v, int w, int o) = 0;

    // Function to remove vertex v and its incident edges
    virtual void removeVertex(int v) = 0;

    // Function to remove edge e
    virtual void removeEdge(int e) = 0;

    // Function to get incident edges of vertex v
    virtual std::vector<int> incidentEdges(int v) = 0;

    // Function to get all vertices in the graph
    virtual std::vector<int> vertices() = 0;

    // Function to get all edges in the graph
    virtual std::vector<int> edges() = 0;

    // Static function to create graph from input stream
    static std::unique_ptr<Graph> createGraph(std::istream &is);

    virtual void printAdjMatrix();
};

#endif /* GRAPH_HPP_ */
