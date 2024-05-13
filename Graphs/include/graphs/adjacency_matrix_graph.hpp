#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <stdexcept>

class AdjacencyMatrixGraph : public Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    explicit AdjacencyMatrixGraph(int vertices) : Graph(vertices) {
        // Initialize the adjacency matrix with all zeros
        adjacencyMatrix.resize(V, std::vector<int>(V, 0));
    }

    void addEdge(int v1, int v2, int weight) override {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacencyMatrix[v1][v2] = weight;
        adjacencyMatrix[v2][v1] = weight; // Assuming undirected graph
    }

    int getEdgeWeight(int v1, int v2) override {
        if (v1 >= V || v2 >= V || v1 < 0 || v2 < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        return adjacencyMatrix[v1][v2];
    }

    std::vector<int> endVertices(int e) override {
        std::vector<int> endpoints;
        for (int i = 0; i < V; ++i) {
            if (adjacencyMatrix[e][i] != 0) {
                endpoints.push_back(i);
            }
        }
        return endpoints;
    }

    int opposite(int v, int e) override {
        if (e >= V || e < 0) {
            throw std::out_of_range("Edge index out of range");
        }
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        if (adjacencyMatrix[v][e] == 0) {
            throw std::invalid_argument("Vertex and edge are not adjacent");
        }
        for (int i = 0; i < V; ++i) {
            if (adjacencyMatrix[v][i] != 0 && i != e) {
                return i;
            }
        }
        throw std::logic_error("No opposite vertex found");
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
        // Assuming 'x' is the new value for vertex 'v'
    }

    void replaceEdge(int e, int x) override {
        if (e >= V || e < 0) {
            throw std::out_of_range("Edge index out of range");
        }
        // Assuming 'x' is the new value for edge 'e'
    }

    void insertVertex(int o) override {
        ++V;
        adjacencyMatrix.resize(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; ++i) {
            adjacencyMatrix[i].resize(V, 0);
        }
        // Assuming 'o' is the new value for the inserted vertex
    }

    void insertEdge(int v, int w, int o) override {
        // Assuming 'o' is the new value for the inserted edge
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
        --V;
    }

    void removeEdge(int e) override {
        if (e >= V || e < 0) {
            throw std::out_of_range("Edge index out of range");
        }
        for (int i = 0; i < V; ++i) {
            adjacencyMatrix[i][e] = 0;
            adjacencyMatrix[e][i] = 0;
        }
    }

    std::vector<int> incidentEdges(int v) override {
        if (v >= V || v < 0) {
            throw std::out_of_range("Vertex index out of range");
        }
        std::vector<int> edges;
        for (int i = 0; i < V; ++i) {
            if (adjacencyMatrix[v][i] != 0) {
                edges.push_back(i);
            }
        }
        return edges;
    }

    std::vector<int> vertices() override {
        std::vector<int> vert;
        for (int i = 0; i < V; ++i) {
            vert.push_back(i);
        }
        return vert;
    }

    std::vector<int> edges() override {
        std::vector<int> edge;
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    edge.push_back(adjacencyMatrix[i][j]);
                }
            }
        }
        return edge;
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

// Function to create graph from input stream

