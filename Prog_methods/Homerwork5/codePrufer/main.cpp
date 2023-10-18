#include <iostream>
#include <vector>

using namespace std;

// Функция для кодирования дерева в последовательность Прюфера
vector<int> pruferCode(int n, vector<pair<int, int>>& edges) {
    vector<int> degree(n, 1);
    vector<int> code;

    for (const auto& edge : edges) {
        degree[edge.first]++;
        degree[edge.second]++;
    }

    int leaf = 0;
    for (int i = 0; i < n - 2; i++) {
        while (degree[leaf] != 1) {
            leaf++;
        }

        int neighbor = -1; // Инициализируем neighbor значением, которого нет в векторе рёбер

        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].first == leaf) {
                neighbor = edges[i].second;
                edges.erase(edges.begin() + i);
                break;
            }
            if (edges[i].second == leaf) {
                neighbor = edges[i].first;
                edges.erase(edges.begin() + i);
                break;
            }
        }

        if (neighbor != -1) {
            code.push_back(neighbor + 1);
            degree[leaf]--;
            degree[neighbor]--;
        }

        code.push_back(neighbor + 1);
        degree[leaf]--;
        degree[neighbor]--;
    }

    return code;
}

int main() {
    int n = 6; // Количество вершин
    vector<pair<int, int>> edges = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6} }; // Рёбра дерева

    vector<int> code = pruferCode(n, edges);

    cout << "Последовательность Прюфера: ";
    for (int i : code) {
        cout << i << " ";
    }

    return 0;
}
