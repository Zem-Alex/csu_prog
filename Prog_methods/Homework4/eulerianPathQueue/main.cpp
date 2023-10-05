#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// ��������� ��� ������������� ����� � ���� ������ ���������
class Graph
{
public:
    int V; // ���������� ������
    vector<vector<int>> adj; // ������ ���������

    Graph(int vertices) : V(vertices)
    {
        adj.resize(V);
    }

    // ���������� ����� � ����
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ����� �������� �������
    int findOddVertex()
    {
        for (int i = 0; i < V; i++)
        {
            if (adj[i].size() % 2 != 0)
            {
                return i;
            }
        }
        return 0; // ���� ��� �������� ������, ������ 0
    }

    bool hasEulerianPath() {
        int oddDegreeCount = 0; // ������� ������ � �������� ��������

        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                oddDegreeCount++;
            }
        }

        // ������� ��� ������� �������� ����:
        // 1. ���� �������
        // 2.  <= 2 ������, ������ ����� �������� �������
        return oddDegreeCount == 0 || oddDegreeCount == 1 || oddDegreeCount == 2;
    }

    // �������� ������ �������� ����
    void eulerianPath()
    {
        if (hasEulerianPath())
        {
            queue<int> Q;
            
            int countOfEdges = 0; 

            for (int i = 0; i < V; i++) {
                countOfEdges += adj[i].size(); // ��������� ������� ������
            }
            countOfEdges /= 2; // и��� ������ ������(����� � ������������)

            Q.push(0); // ������ � ������������(�������) �������

            while (Q.size() <= countOfEdges)
            {
                int u = Q.back();
                if (!adj[u].empty())
                {
                    int v = adj[u].back(); // ������� ���������� ������ ������� u
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

            // ������� ������� ����(���������� ������� Q
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
    Graph g(5); // ������� ���� � 5 ���������

    // ��������� �����
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
