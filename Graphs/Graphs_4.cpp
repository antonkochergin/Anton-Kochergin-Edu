#include <iostream>
#include <vector>
#include <queue>

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
            cout << "Ошибка: неверные номера вершин! Повторите ввод." << endl;
            i--;
            continue;
        }

        graph[x].push_back(y);
    }

    // Удаление дубликатов и сортировка
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

void findUnreachableVertices(const vector<vector<int>>& graph) {
    int start;
    cout << "Введите начальную вершину: ";
    cin >> start;

    if (start < 0 || start >= graph.size()) {
        cout << "Ошибка: неверный номер вершины!" << endl;
        return;
    }

    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    // Обход в ширину (BFS)
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // Вывод недостижимых вершин
    cout << "Недостижимые вершины из " << start << ": ";
    bool allReachable = true;
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            cout << i << " ";
            allReachable = false;
        }
    }

    if (allReachable) {
        cout << "все вершины достижимы";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createDirectedGraph();
    findUnreachableVertices(graph);
    return 0;
}