#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();

struct Edge 
{
    int src, dest, weight;
};

class Graph 
{
public:
    Graph(const std::string& filename);
    void runAlgorithm(int option);

private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
    std::vector<std::vector<int>> graph;

    void convertToAdjacencyList();
    bool isConnected();
    int findParent(std::vector<int>& parent, int vertex);
    void unionVertices(std::vector<int>& parent, int u, int v);
    std::vector<Edge> kruskalMST();
    std::vector<Edge> primMST();
    void writeEdgesToFile(const std::vector<Edge>& edges, const std::string& outputFile);
};

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

void Graph::convertToAdjacencyList() 
{
    int n = graph.size();
    adjacencyList.resize(n);

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (graph[i][j] != 0) 
            {
                adjacencyList[i].push_back({ j, graph[i][j] });
            }
        }
    }
}

void Graph::runAlgorithm(int option) 
{
    std::vector<Edge> edges;

    std::string outputFile = "output.txt";

    switch (option) 
    {
    case 1:
        if (!isConnected())
        {
            std::cout << "Graph is not connected!" << std::endl;
            return;
        }
        edges = kruskalMST();
       
        if (edges.empty())
        {
            std::cout << "Graph is not connected!" << std::endl;
        }
        else {
            int totalWeight = 0;
            for (const auto& edge : edges) {
                totalWeight += edge.weight;
            }
            std::cout << "Weight of minimum spanning tree: " << totalWeight << std::endl;

            writeEdgesToFile(edges, outputFile);
        }

        edges = primMST();
        //break;
    case 2:
        if (!isConnected()) 
        {
            std::cout << "Graph is not connected!" << std::endl;
            return;
        }
        edges = primMST();
        break;
    default:
        std::cout << "Invalid option!" << std::endl;
        return;
    }

    if (edges.empty()) 
    {
        std::cout << "Graph is not connected!" << std::endl;
    }
    else {
        int totalWeight = 0;
        for (const auto& edge : edges) {
            totalWeight += edge.weight;
        }
        std::cout << "Weight of minimum spanning tree: " << totalWeight << std::endl;
        
        writeEdgesToFile(edges, outputFile);
    }
}

bool Graph::isConnected() 
{
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(0);
    visited[0] = true;

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) 
        {
            if (graph[u][v] != 0 && !visited[v]) 
            {
                q.push(v);
                visited[v] = true;
            }
        }
    }

    return (std::find(visited.begin(), visited.end(), false) == visited.end());
}

std::vector<Edge> Graph::kruskalMST() 
{
    convertToAdjacencyList(); // Преобразование из матрицы смежности в список смежности

    int n = adjacencyList.size();
    std::vector<Edge> edges;

    for (int i = 0; i < n; ++i) 
    {
        for (const auto& edge : adjacencyList[i]) 
        {
            int j = edge.first;
            int weight = edge.second;
            edges.push_back({ i, j, weight });
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    std::vector<Edge> result;
    std::vector<int> parent(n, -1);

    int edgeCount = 0, i = 0;
    while (edgeCount < n - 1 && i < edges.size()) 
    {
        Edge nextEdge = edges[i++];

        int u = findParent(parent, nextEdge.src);
        int v = findParent(parent, nextEdge.dest);

        if (u != v) 
        {
            result.push_back(nextEdge);
            unionVertices(parent, u, v);
            edgeCount++;
        }
    }

    return result;
}

std::vector<Edge> Graph::primMST() 
{
    convertToAdjacencyList(); // Преобразование из матрицы смежности в список смежности

    int n = adjacencyList.size();
    std::vector<Edge> result;
    std::vector<int> key(n, INF);
    std::vector<int> parent(n, -1);
    std::vector<bool> inQ(n, true);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int randomVertex = 0;
    key[randomVertex] = 0;
    pq.push({ 0, randomVertex });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inQ[u] = false;

        for (const auto& edge : adjacencyList[u]) 
        {
            int v = edge.first;
            int weight = edge.second;

            if (inQ[v] && weight < key[v]) 
            {
                parent[v] = u;
                key[v] = weight;
                pq.push({ key[v], v });
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        result.push_back({ parent[i], i, key[i] });
    }

    return result;
}


int Graph::findParent(std::vector<int>& parent, int vertex) 
{
    if (parent[vertex] == -1) 
    {
        return vertex;
    }
    return findParent(parent, parent[vertex]);
}

void Graph::unionVertices(std::vector<int>& parent, int u, int v) 
{
    int uSet = findParent(parent, u);
    int vSet = findParent(parent, v);
    parent[uSet] = vSet;
}

void Graph::writeEdgesToFile(const std::vector<Edge>& edges, const std::string& outputFile) 
{
    int totalWeight = 0;
    std::ofstream outputFileStream(outputFile);
    if (!outputFileStream.is_open()) 
    {
        std::cout << "Unable to open the output file!" << std::endl;
        return;
    }

    for (const auto& edge : edges) 
    {
        totalWeight += edge.weight;
        outputFileStream << edge.src << " " << edge.dest << " " << edge.weight << std::endl;
    }

    outputFileStream.close();
    std::cout << "Edges written to file: " << outputFile << std::endl;
}