#include <iostream>
#include <vector>
#include <stack>

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
            int startVertex = findOddVertex(); // ������ � �������� ������� ��� 0
            stack<int> S;
            vector<int> path; // ������ ��� �������� �������� ����

            S.push(startVertex);


            while (!S.empty())
            {
                int u = S.top();
                if (!adj[u].empty())
                {
                    int v = adj[u].back(); // ������� ���������� ������ ������� u
                    adj[u].pop_back();
                    for (int i = 0; i < adj[v].size(); i++)
                    {
                        if (adj[v][i] == u)
                        {
                            adj[v].erase(adj[v].begin() + i);
                            break;
                        }
                    }
                    S.push(v);
                }
                else {
                    path.push_back(u);
                    S.pop();
                }
            }

            // ������� ������� ����
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << path[i];
                if (i != 0)
                {
                    cout << " -> ";
                }
            }
            cout << endl;
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
