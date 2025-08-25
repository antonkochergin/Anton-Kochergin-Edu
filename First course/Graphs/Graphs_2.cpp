#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> createDirectedGraph() {
    int n, m;
    cout << "Введите количество вершин (N): ";
    cin >> n;
    cout << "Введите количество ребер (M): ";
    cin >> m;

    vector<vector<int>> graph(n);
    cout << "Введите " << m << " ребер в формате x y:" << endl;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        if (x >= n || y >= n || x < 0 || y < 0) {
            cout << "Ошибка: неверные номера вершин!" << endl;
            i--;
            continue;
        }

        graph[x].push_back(y);
    }

    // Удаляем дубликаты и сортируем
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

void addEdge(vector<vector<int>>& graph) {
    int a, b;
    cout << "Введите ребро для добавления (A B): ";
    cin >> a >> b;

    if (a < 0 || b < 0 || a >= graph.size() || b >= graph.size()) {
        cout << "Ошибка: неверные номера вершин!" << endl;
        return;
    }

    // Проверяем, существует ли уже такое ребро
    if (find(graph[a].begin(), graph[a].end(), b) != graph[a].end()) {
        cout << "Ребро уже существует!" << endl;
        return;
    }

    graph[a].push_back(b);
    sort(graph[a].begin(), graph[a].end());
    cout << "Ребро " << a << " -> " << b << " успешно добавлено" << endl;
}

void printGraph(const vector<vector<int>>& graph) {
    cout << "\nСписок смежности:" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << ": ";
        for (int v : graph[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createDirectedGraph();
    printGraph(graph);
    addEdge(graph);
    printGraph(graph);
    return 0;
}