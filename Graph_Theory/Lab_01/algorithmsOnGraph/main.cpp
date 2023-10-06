#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "graph.hpp" 


int main() 
{
    setlocale(LC_ALL, "ru");
    std::ifstream inputFile("test6.txt");
    int n, option;
    inputFile >> n;
    Graph graph("test6.txt");

    std::cout << "Выберите алгоритм:" << std::endl
        << "1) Алгоритм Дейкстры" << std::endl
        << "2) Алгоритм Форда-Беллмана" << std::endl
        << "3) Алгоритм Флойда–Уоршелла" << std::endl;
    std::cin >> option;

    graph.runAlgorithm(option);

    return 0;
}
