#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// Функция для создания ориентированного графа
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

// Первый проход DFS (заполнение стека порядком завершения обработки вершин)
void dfsFirstPass(int v, const vector<vector<int>>& graph, vector<bool>& visited, stack<int>& order) {
    visited[v] = true;
    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfsFirstPass(neighbor, graph, visited, order);
        }
    }
    order.push(v);
}

// Второй проход DFS (поиск компоненты сильной связности)
void dfsSecondPass(int v, const vector<vector<int>>& transposedGraph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : transposedGraph[v]) {
        if (!visited[neighbor]) {
            dfsSecondPass(neighbor, transposedGraph, visited, component);
        }
    }
}

// Функция для нахождения всех сильно связных компонент (алгоритм Косарайю)
vector<vector<int>> findStronglyConnectedComponents(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> order;

    // 1. Первый проход DFS - заполнение стека
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsFirstPass(i, graph, visited, order);
        }
    }

    // 2. Транспонирование графа
    vector<vector<int>> transposedGraph(n);
    for (int v = 0; v < n; ++v) {
        for (int neighbor : graph[v]) {
            transposedGraph[neighbor].push_back(v);
        }
    }

    // 3. Второй проход DFS в порядке убывания времени завершения
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> components;

    while (!order.empty()) {
        int v = order.top();
        order.pop();

        if (!visited[v]) {
            vector<int> component;
            dfsSecondPass(v, transposedGraph, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

// Функция для вывода результатов
void printComponents(const vector<vector<int>>& components) {
    cout << "\nСильно связные компоненты:" << endl;
    for (int i = 0; i < components.size(); ++i) {
        cout << "Компонента " << i + 1 << ": ";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createDirectedGraph();
    auto components = findStronglyConnectedComponents(graph);
    printComponents(components);
    return 0;
}