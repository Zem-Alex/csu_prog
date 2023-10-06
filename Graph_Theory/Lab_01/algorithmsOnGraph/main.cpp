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

    std::cout << "�������� ��������:" << std::endl
        << "1) �������� ��������" << std::endl
        << "2) �������� �����-��������" << std::endl
        << "3) �������� ���������������" << std::endl;
    std::cin >> option;

    graph.runAlgorithm(option);

    return 0;
}
