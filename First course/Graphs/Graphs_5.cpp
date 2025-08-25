#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// ������� ��� �������� ���������������� �����
vector<vector<int>> createDirectedGraph() {
    int n, m;
    cout << "������� ���������� ������ (N): ";
    cin >> n;
    cout << "������� ���������� ����� (M): ";
    cin >> m;

    vector<vector<int>> graph(n);
    cout << "������� " << m << " ����� � ������� x y:" << endl;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        if (x >= n || y >= n || x < 0 || y < 0) {
            cout << "������: �������� ������ ������! ��������� ����." << endl;
            i--;
            continue;
        }

        graph[x].push_back(y);
    }

    // �������� ���������� � ����������
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

// ������ ������ DFS (���������� ����� �������� ���������� ��������� ������)
void dfsFirstPass(int v, const vector<vector<int>>& graph, vector<bool>& visited, stack<int>& order) {
    visited[v] = true;
    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfsFirstPass(neighbor, graph, visited, order);
        }
    }
    order.push(v);
}

// ������ ������ DFS (����� ���������� ������� ���������)
void dfsSecondPass(int v, const vector<vector<int>>& transposedGraph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : transposedGraph[v]) {
        if (!visited[neighbor]) {
            dfsSecondPass(neighbor, transposedGraph, visited, component);
        }
    }
}

// ������� ��� ���������� ���� ������ ������� ��������� (�������� ��������)
vector<vector<int>> findStronglyConnectedComponents(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> order;

    // 1. ������ ������ DFS - ���������� �����
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsFirstPass(i, graph, visited, order);
        }
    }

    // 2. ���������������� �����
    vector<vector<int>> transposedGraph(n);
    for (int v = 0; v < n; ++v) {
        for (int neighbor : graph[v]) {
            transposedGraph[neighbor].push_back(v);
        }
    }

    // 3. ������ ������ DFS � ������� �������� ������� ����������
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

// ������� ��� ������ �����������
void printComponents(const vector<vector<int>>& components) {
    cout << "\n������ ������� ����������:" << endl;
    for (int i = 0; i < components.size(); ++i) {
        cout << "���������� " << i + 1 << ": ";
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