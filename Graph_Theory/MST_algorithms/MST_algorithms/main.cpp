#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "header.hpp" 
#include <chrono>

int main() {
    char strin[] = "test0.txt";
    auto begin = std::chrono::steady_clock::now();
    

    
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
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    }
    
    

    return 0;
}