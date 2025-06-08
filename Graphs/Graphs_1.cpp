#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> createGraph() {
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
            cout << "������: �������� ������ ������!" << endl;
            i--;
            continue;
        }

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    // ������� ��������� � ���������
    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    return graph;
}

void printAdjacentCount(const vector<vector<int>>& graph) {
    int vertex;
    cout << "������� �������: ";
    cin >> vertex;

    if (vertex < 0 || vertex >= graph.size()) {
        cout << "������: �������� ����� �������!" << endl;
        return;
    }

    cout << "���������� ������� ������: " << graph[vertex].size() << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto graph = createGraph();
    printAdjacentCount(graph);
    return 0;
}