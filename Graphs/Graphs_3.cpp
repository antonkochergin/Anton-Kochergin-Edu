#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> createUndirectedGraph() {
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
            cout << "Ошибка: неверные номера вершин! Повторите ввод." << endl;
            i--;
            continue;
        }

        graph[x].push_back(y);
        graph[y].push_back(x); // Для неориентированного графа
    }

    // Удаление дубликатов и сортировка
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

void printVertexDegrees(const vector<vector<int>>& graph) {
    cout << "\nСтепени вершин:" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        // Степень вершины равна количеству смежных вершин
        // Для неориентированного графа это просто размер списка смежности
        cout << "Вершина " << i << ": степень " << graph[i].size() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createUndirectedGraph();
    printVertexDegrees(graph);
    return 0;
}