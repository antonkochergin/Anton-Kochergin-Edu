#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> createGraph() {
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
        graph[y].push_back(x);
    }

    // Удаляем дубликаты и сортируем
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

void printAdjacentCount(const vector<vector<int>>& graph) {
    int vertex;
    cout << "Введите вершину: ";
    cin >> vertex;

    if (vertex < 0 || vertex >= graph.size()) {
        cout << "Ошибка: неверный номер вершины!" << endl;
        return;
    }

    cout << "Количество смежных вершин: " << graph[vertex].size() << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createGraph();
    printAdjacentCount(graph);
    return 0;
}