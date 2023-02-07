// Формула для нахождения расстояния между двумя точками: ((x1-x2)^2+(y1-y2)+(z1-z1))^(1/2)
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

typedef struct Point
{
    int x, y, z;
} Point;

int main()
{
    Point pointCenter = { 0, 0, 0 }, points[] = { {1, 2, 3}, {2, 3, 4}, {3, 4, 5} };
    double distance = 0;

    for (int i = 0; i < 3; i++)
    {
        distance = sqrt(pow(points[i].x - pointCenter.x, 2.0) + pow(points[i].y - pointCenter.y, 2.0) + pow(points[i].z - pointCenter.z, 2.0));
        cout << distance << endl;
    }

    std::string line;

    std::ifstream in("input.xml"); // окрываем файл для чтения
    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            //points[i] = line;
            i++;
        }
    }
    in.close();     // закрываем файл

    std::cout << "End of program" << std::endl;

    return 0;
}