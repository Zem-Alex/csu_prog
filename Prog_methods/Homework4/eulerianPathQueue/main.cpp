#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Структура для представления графа в виде списка смежности
class Graph
{
public:
    int V; // Количество вершин
    vector<vector<int>> adj; // Список смежности

    Graph(int vertices) : V(vertices)
    {
        adj.resize(V);
    }

    // Добавление ребра в граф
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Поиск нечетной вершины
    int findOddVertex()
    {
        for (int i = 0; i < V; i++)
        {
            if (adj[i].size() % 2 != 0)
            {
                return i;
            }
        }
        return 0; // Если нет нечетных вершин, вернем 0
    }

    bool hasEulerianPath() {
        int oddDegreeCount = 0; // Счетчик вершин с нечетной степенью

        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                oddDegreeCount++;
            }
        }

        // Условия для наличия Эйлерова пути:
        // 1. Граф связный
        // 2.  <= 2 вершин, должны иметь нечетную степень
        return oddDegreeCount == 0 || oddDegreeCount == 1 || oddDegreeCount == 2;
    }

    // Алгоритм поиска Эйлерова пути
    void eulerianPath()
    {
        if (hasEulerianPath())
        {
            queue<int> Q;
            
            int countOfEdges = 0; 

            for (int i = 0; i < V; i++) {
                countOfEdges += adj[i].size(); // Суммируем степени вершин
            }
            countOfEdges /= 2; // Рёбра учтены дважды(лемма о рукопожатиях)

            Q.push(0); // начнем с произвольной(нулевой) вершины

            while (Q.size() <= countOfEdges)
            {
                int u = Q.back();
                if (!adj[u].empty())
                {
                    int v = adj[u].back(); // Возьмем последнего соседа вершины u
                    adj[u].pop_back();

                    auto it = std::find(adj[v].begin(), adj[v].end(), u);
                    if (it != adj[v].end()) 
                    {
                        adj[v].erase(it);
                    }

                    Q.push(v);
                }
                else {
                    Q.pop();
                    Q.push(Q.front());
                }
            }

            // Выводим Эйлеров путь(содержимое очереди Q
            while (!Q.empty()) 
            {
                cout << Q.front() << " ";
                Q.pop();
            }
        }
        else
        {
            cout << "None" << endl;
        }
    }
};

int main()
{
    Graph g(5); // Создаем граф с 5 вершинами

    // Добавляем ребра
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    cout << "Eulerian Path: ";
    g.eulerianPath();

    return 0;
}
