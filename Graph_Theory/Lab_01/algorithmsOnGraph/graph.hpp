#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class Graph
{
public:
    Graph(const std::string& filename);
    void runAlgorithm(int option);

private:
    std::vector<std::vector<int>> graph;

    void dijkstra(int startVertex, std::vector<int>& distances);
    void bellmanFord(int startVertex, std::vector<int>& distances);
    void floydWarshall();
    void writeDistToFile(const std::string& filename, std::vector<int>& distances) const;
    void writeMatrixToFile(const std::string& filename) const;
};

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>



Graph::Graph(const std::string& filename)
{
    std::ifstream inputFile(filename);
    int n;
    inputFile >> n;
    graph.resize(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            inputFile >> graph[i][j];
        }
    }
}

void Graph::runAlgorithm(int option)
{
    int startVertex = 0;
    std::vector<int> distances;

    distances.assign(graph.size(), INF);
    switch (option)
    {
    case 1:
        std::cout << "Введите начальную вершину: ";
        std::cin >> startVertex;
        dijkstra(startVertex, distances);
        break;

    case 2:
        std::cout << "Введите начальную вершину: ";
        std::cin >> startVertex;
        bellmanFord(startVertex, distances);
        break;

    case 3:
        floydWarshall();
        writeMatrixToFile("output.txt");
        break;

    default:
        std::cout << "Такого алгоритма нет!" << std::endl;
        return;
    }

    if (option != 3)
    {
        writeDistToFile("output.txt", distances);
        
    }
}

void Graph::dijkstra(int startVertex, std::vector<int>& distances)
{
    int n = graph.size();
    std::vector<bool> used(n, false);
    distances.assign(n, INF);
    distances[startVertex] = 0;

    for (int i = 0; i < n; ++i)
    {
        int v = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!used[j] && (v == -1 || distances[j] < distances[v]))
            {
                v = j;
            }
        }

        if (distances[v] == INF)
        {
            break;
        }

        used[v] = true;

        for (int u = 0; u < n; ++u)
        {
            if (graph[v][u] != 0 && distances[v] != INF && distances[v] + graph[v][u] < distances[u])
            {
                distances[u] = distances[v] + graph[v][u];
            }
        }
    }
}

void Graph::bellmanFord(int startVertex, std::vector<int>& distances)
{
    int n = graph.size();
    distances.assign(n, INF);
    distances[startVertex] = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (graph[u][v] != 0 && distances[u] != INF && distances[u] + graph[u][v] < distances[v])
                {
                    distances[v] = distances[u] + graph[u][v];
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            if (graph[u][v] != 0 && distances[u] != INF && distances[u] + graph[u][v] < distances[v])
            {
                std::cout << "Граф содержит отрицательный цикл." << std::endl;
                return;
            }
        }
    }
}

void Graph::floydWarshall()
{
    int n = graph.size();

    // Инициализация начальных значений
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else if (graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (graph[i][k] < INF && graph[k][j] < INF)
                {
                    graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
}

void Graph::writeDistToFile(const std::string& filename, std::vector<int>& distances) const
{
    std::ofstream outputFile(filename);
     
        for (int element : distances) {
            if (element == INF) {
                outputFile << "INF ";
            }
            else {
                outputFile << element << " ";
            }
        }
        outputFile << std::endl;
}

void Graph::writeMatrixToFile(const std::string& filename) const
{
    std::ofstream outputFile(filename);
    for (const auto& row : graph) {
        for (int element : row) {
            if (element == INF) {
                outputFile << "INF ";
            }
            else {
                outputFile << element << " ";
            }
        }
        outputFile << std::endl;
    }
}