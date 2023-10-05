#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>

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

    void printEdges() {
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                if (u < v) {
                    cout << u << " - " << v << endl;
                }
            }
        }
    }
};

// Генерация случайного Эйлерова графа с n вершинами и m рёбрами
Graph generateRandomEulerGraph(int n, int m)
{
    Graph g(n);

    if (n >= 2 && m >= n && m <= n * (n - 1) / 2)
    {
        srand(static_cast<unsigned>(time(0)));

        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                edges.push_back({ i, j });
            }
        }

        random_shuffle(edges.begin(), edges.end());

        for (int i = 0; i < m; i++)
        {
            g.addEdge(edges[i].first, edges[i].second);
        }
    }
    return g;
}

int main()
{
    srand(time(NULL));
    int n = 5; // Количество вершин
    int m = 6; // Количество рёбер

    Graph g = generateRandomEulerGraph(n, m);

    cout << "Edges of the graph:" << endl;
    g.printEdges();

    cout << "Eulerian Path: ";
    g.eulerianPath();

    return 0;
}
