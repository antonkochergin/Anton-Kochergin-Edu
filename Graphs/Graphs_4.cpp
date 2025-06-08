#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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

void findUnreachableVertices(const vector<vector<int>>& graph) {
    int start;
    cout << "������� ��������� �������: ";
    cin >> start;

    if (start < 0 || start >= graph.size()) {
        cout << "������: �������� ����� �������!" << endl;
        return;
    }

    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    // ����� � ������ (BFS)
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

    // ����� ������������ ������
    cout << "������������ ������� �� " << start << ": ";
    bool allReachable = true;
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            cout << i << " ";
            allReachable = false;
        }
    }

    if (allReachable) {
        cout << "��� ������� ���������";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createDirectedGraph();
    findUnreachableVertices(graph);
    return 0;
}