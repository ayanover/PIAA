#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "Graph.hpp"

class AdjacencyMatrixGraph : public Graph
{
private:
    std::vector<std::vector<int>> adjMatrix; // Adjacency matrix
    std::vector<int> elements;               // Elements stored at vertices

public:
    // Explicit constructor to avoid implicit conversions
    explicit AdjacencyMatrixGraph(int vertices) : Graph(vertices)
    {
        // Initialize adjacency matrix with V x V size
        adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
        elements.resize(vertices);
    }

    // Function to add an edge between v1 and v2
    void addEdge(int v1, int v2, int weight) override
    {
        adjMatrix[v1][v2] = 1;
        adjMatrix[v2][v1] = 1; // Undirected graph, so add edge in both directions
    }

    // Function to print the adjacency matrix

    std::vector<int> endVertices(int e) override
    {
        if (e >= adjMatrix.size() || e >= adjMatrix[0].size() || adjMatrix[e][e] == 0)
            return {-1, -1}; // Invalid edge

        for (int i = 0; i < V; ++i)
        {
            if (adjMatrix[e][i] != 0)
                return {e, i};
        }

        return {-1, -1}; // Should not reach here
    }

    int opposite(int v, int e) override
    {
        if (adjMatrix[v][e] == 0)
            return -1; // Vertex v is not incident on edge e

        for (int i = 0; i < V; ++i)
        {
            if (adjMatrix[v][i] != 0 && i != e)
                return i;
        }

        return -1; // Should not reach here
    }

    bool areAdjacent(int v, int w) override
    {
        return (adjMatrix[v][w] != 0);
    }

    void replace(int v, int x) override
    {
        if (v < elements.size())
            elements[v] = x;
    }

    void replaceEdge(int e, int x) override
    {

    }


    void insertVertex(int o) override
    {
        for (int i = 0; i < V; ++i)
        {
            adjMatrix[i].emplace_back(0);
        }
        adjMatrix.emplace_back(std::vector<int>(V + 1, 0));
        elements.emplace_back(o);
        V++;
    }


    void insertEdge(int v, int w, int o) override
    {
        if (v >= V || w >= V)
            return;

        adjMatrix[v][w] = 1;
        adjMatrix[w][v] = 1;
    }


    void removeVertex(int v) override
    {
        if (v >= V)
            return; // Invalid vertex

        for (int i = 0; i < V; ++i)
        {
            adjMatrix[i].erase(adjMatrix[i].begin() + v);
        }
        adjMatrix.erase(adjMatrix.begin() + v);
        elements.erase(elements.begin() + v);
        V--;
    }


    void removeEdge(int e) override
    {
        if (e >= V || e >= adjMatrix.size() || e >= adjMatrix[0].size())
            return;

        for (int i = 0; i < V; ++i)
        {
            adjMatrix[i][e] = 0;
            adjMatrix[e][i] = 0;
        }
    }

    std::vector<int> incidentEdges(int v) override
    {
        std::vector<int> incidentEdges;
        if (v >= V)
            return incidentEdges; // Invalid vertex

        for (int i = 0; i < V; ++i)
        {
            if (adjMatrix[v][i] != 0)
                incidentEdges.emplace_back(i);
        }

        return incidentEdges;
    }


    std::vector<int> vertices() override
    {
        std::vector<int> result;
        for (int i = 0; i < V; ++i)
            result.emplace_back(i);
        return result;
    }


    std::vector<int> edges() override
    {
        std::vector<int> result;
        for (int i = 0; i < V; ++i)
        {
            for (int j = i + 1; j < V; ++j) // Considering upper triangle of the matrix
            {
                if (adjMatrix[i][j] != 0)
                    result.emplace_back(adjMatrix[i][j]);
            }
        }
        return result;
    }

    // Static function to create graph from input stream
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
