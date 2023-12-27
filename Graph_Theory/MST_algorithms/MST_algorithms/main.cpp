#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "header.hpp" 

int main() {
    char strin[] = "test0.txt";
    for (size_t i = 1; i <= 6; i++)
    {
        std::cout << "test " << i << std::endl;
        char stri = i + 48;
        strin[4] = stri;
        Graph graph(strin);
        int option = 1;
        //std::cout << "Choose algorithm (1 - Kruskal, 2 - Prim): ";
        //std::cin >> option;
        graph.runAlgorithm(option);
        std::cout << std::endl;
    }
        return 0;
}