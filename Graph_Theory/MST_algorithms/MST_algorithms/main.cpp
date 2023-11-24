#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "header.hpp" 

int main() {
    Graph graph("test4.txt"); 
    int option;
    std::cout << "Choose algorithm (1 - Kruskal, 2 - Prim): ";
    std::cin >> option;
    graph.runAlgorithm(option);
    return 0;
}