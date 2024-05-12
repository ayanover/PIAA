#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include "Graph.hpp"

class AdjacencyListGraph : public Graph
{
private:
    struct Edge
    {
        int dest;
        int weight;
        Edge(int d, int w) : dest(d), weight(w) {}
    };

    std::vector<std::vector<Edge>> adjList;
    std::vector<int> elements;

public:
    explicit AdjacencyListGraph(int vertices) : Graph(vertices)
    {
        adjList.resize(vertices);
        elements.resize(vertices);
    }

    void addEdge(int v1, int v2, int weight) override
    {
        adjList[v1].emplace_back(v2, weight);
        adjList[v2].emplace_back(v1, weight);
    }

    int getEdgeWeight(int v1, int v2) override
    {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0)
        {
            return -1;
        }

        for (const Edge &edge : adjList[v1])
        {
            if (edge.dest == v2)
            {
                return edge.weight;
            }
        }

        return -1;
    }

    void printAdjList() override
    {
        for (int i = 0; i < V; ++i)
        {
            std::cout << "Vertex " << i << " :";
            for (const Edge &edge : adjList[i])
            {
                std::cout << " -> " << edge.dest << " (Weight: " << edge.weight << ")";
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> endVertices(int e) override
    {
        if (e >= adjList.size() || adjList[e].empty())
            return {-1, -1};

        return {e, adjList[e][0].dest};
    }

    int opposite(int v, int e) override
    {
        if (adjList[v].empty())
            return -1;

        for (const Edge &edge : adjList[v])
        {
            if (edge.dest == e)
            {
                return v;
            }
        }
        return -1;
    }


    bool areAdjacent(int v, int w) override
    {
        for (const Edge &edge : adjList[v])
        {
            if (edge.dest == w)
                return true;
        }
        return false;
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
        adjList.emplace_back(std::vector<Edge>());
        elements.push_back(o);
        V++;
    }


    void insertEdge(int v, int w, int o) override
    {
        if (v >= V || w >= V)
            return;

        adjList[v].emplace_back(w, o);
        adjList[w].emplace_back(v, o);
    }


    void removeVertex(int v) override
    {
        if (v >= V)
            return;

        for (int i = 0; i < adjList[v].size(); ++i)
        {
            int adjacentVertex = adjList[v][i].dest;
            auto it = std::find_if(adjList[adjacentVertex].begin(), adjList[adjacentVertex].end(), [v](const Edge &edge) { return edge.dest == v; });
            if (it != adjList[adjacentVertex].end())
                adjList[adjacentVertex].erase(it);
        }

        adjList.erase(adjList.begin() + v);
        elements.erase(elements.begin() + v);
        V--;
    }


    void removeEdge(int e) override
    {

    }


    std::vector<int> incidentEdges(int v) override
    {
        if (v >= V)
            return std::vector<int>();

        std::vector<int> result;
        for (const Edge &edge : adjList[v])
        {
            result.push_back(edge.dest);
        }
        return result;
    }


    std::vector<int> vertices() override
    {
        std::vector<int> result;
        for (int i = 0; i < V; ++i)
            result.push_back(i);
        return result;
    }


    std::vector<int> edges() override
    {
        std::vector<int> result;
        for (int i = 0; i < V; ++i)
        {
            for (const Edge &edge : adjList[i])
            {
                if (edge.dest >= i)
                    result.push_back(edge.dest);
            }
        }
        return result;
    }

    std::unique_ptr<Graph> createGraph(std::istream &is);
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
