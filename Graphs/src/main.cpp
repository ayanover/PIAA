#include <iostream>
#include <fstream>
#include "adjacency_list_graph.cpp"

int main(int argc, char* argv[])
{
    std::cout<< "Tu wykonujemy testy efektywności algorytmów"<<std::endl;
    std::ifstream graphFile("../sp_data/graph/graphV10D0.5.txt");
    if (!graphFile)
    {
        std::cerr << "Error: Unable to open graph data file." << std::endl;
        return 1;
    }

    Graph graph = c



    return 0;
}
