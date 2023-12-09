#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
    Graph(const std::string& filename);
    void runBronKerbosch();
    void printResults();

private:
    std::vector<std::vector<int>> graph;
    std::vector<int> S;  // текущее независимое множество
    std::vector<int> Qplus;  // множество вершин, которые могут быть добавлены к S
    std::vector<int> Qminus;  // множество вершин, которые уже использовались для расширения S

    std::vector<std::vector<int>> maximalIndependentSets;
    
    int maxInd = 0;

    void extend(std::vector<int> S, std::vector<int> Qplus, std::vector<int> Qminus);
    void bronKerbosch();
    bool check_candidates(const std::vector<int>& candidates, const std::vector<int>& wrong) const;
    
};

Graph::Graph(const std::string& filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int numVertices;
    inputFile >> numVertices;

    graph.resize(numVertices, std::vector<int>(numVertices));

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            inputFile >> graph[i][j];
        }
    }

    inputFile.close();
}


bool Graph::check_candidates(const std::vector<int>& Qplus, const std::vector<int>& Qminus) const
{
    for (int i : Qminus)
    {
        bool q = true;
        for (int j : Qplus)
        {
            if (graph[i][j] != 0)
            {
                q = false;
                break;
            }
        }
        if (q)
            return false;
    }
    return true;
}
void Graph::extend(std::vector<int> S, std::vector<int> Qplus, std::vector<int> Qminus)
{
    while (!Qplus.empty() && check_candidates(Qplus, Qminus))
    {
        int v = Qplus.front();
        

        S.push_back(v);
        std::vector<int> newQplus;
        std::vector<int> newQminus;

        for (int u : Qplus)
        {
            if (graph[v][u] == 0 && u != v)
            {
                newQplus.push_back(u);
            }
        }

        for (int u : Qminus)
        {
            if (graph[v][u] == 0)
            {
                newQminus.push_back(u);
            }
        }
      
        if (newQplus.empty())
        {
            if (newQminus.empty())
            {
                maximalIndependentSets.push_back(S);
                if (maxInd < S.size())
                    maxInd = S.size();
            }
        }
        else
        {
            extend(S, newQplus, newQminus);
        }

        //S.pop_back();
        //Qplus.pop_back();    

        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == v)
            {
                S.erase(S.begin() + i);
                break;
            }
        }
        for (int i = 0; i < Qplus.size(); i++)
        {
            if (Qplus[i] == v)
            {
                Qplus.erase(Qplus.begin() + i);
                break;
            }
        }

        Qminus.push_back(v);
    }
}

void Graph::bronKerbosch()
{
    Qplus.clear();
    for (int i = 0; i < graph.size(); ++i)
    {
        Qplus.push_back(i);
    }

    // Инициализация Qminus
    Qminus.clear();

    extend(S, Qplus, Qminus);
}

void Graph::runBronKerbosch()
{
        bronKerbosch();
}

void Graph::printResults()
{
    //std::cout << "Number of vertices: " << graph.size() << std::endl;
    std::cout << "Number of independent: " << maxInd << std::endl;
    std::cout << "Number of independent sets: " << maximalIndependentSets.size() << std::endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ofstream outputFile("output.txt");

    /*for (const auto& independentSet : maximalIndependentSets)
    {
        std::cout << "Maximal Independent Set: ";
        for (int vertex : independentSet)
        {
            std::cout << vertex << " ";
            outputFile << vertex << " ";
        }
        std::cout << std::endl;
        outputFile << std::endl;
    }*/

    outputFile.close();
}


int main()
{
    Graph graph("test4.txt");
    graph.runBronKerbosch();
    graph.printResults();

    return 0;
}
