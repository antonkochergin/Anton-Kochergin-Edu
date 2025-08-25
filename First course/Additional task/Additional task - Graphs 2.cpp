//��� ����������������� ���������� ����. 
//����� ���������� ���������� �� �������� ������� �� ���� ��������� ������.
//������� �� ������ ����� ����, �� � ��� ���� ����. �������� ��������� ��������������.
//� ������� ���������� �������� ��������
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int INF = 1e9;

struct queue {
    int vertex;
    int distance;
    queue* next;
};

void push(queue*& head, queue*& tail, int vertex, int distance) {
    queue* new_node = new queue;
    new_node->vertex = vertex;
    new_node->distance = distance;
    new_node->next = NULL;

    if (!head) {
        head = tail = new_node;
    }
    else if (distance < head->distance) {
        new_node->next = head;
        head = new_node;
    }
    else {
        queue* current = head;
        while (current->next && current->next->distance <= distance) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        if (!new_node->next) {
            tail = new_node;
        }
    }
}

int pop(queue*& head, queue*& tail) {
    if (!head) return -1;

    queue* temp = head;
    int vertex = head->vertex;
    head = head->next;
    if (!head) tail = NULL;
    delete temp;
    return vertex;
}
//���� �����
vector<vector<pair<int, int>>> createlist() {
    int n, m;

    cout << "������� ���������� ������ (N): ";
    cin >> n;
    cout << "������� ���������� ����� (M): ";
    cin >> m;

    vector<vector<pair<int, int>>> graph(n);

    cout << "������� " << m << " ����� � ������� x y w (w - ��� �����):" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;

        if (x >= n || y >= n) {
            cout << "������: ������� " << x << " ��� " << y << " ��� ���������" << endl;
            continue;
        }

        graph[x].push_back(make_pair(y, w));
        graph[y].push_back(make_pair(x, w));
    }

    for (int i = 0; i < n; ++i) {
        sort(graph[i].begin(), graph[i].end());
        graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
    }

    return graph;
}
//����� �����
void printpaths(vector<int>& dist, vector<int>& prev, int start) {
    cout << "���������� ���������� �� ������� " << start << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        cout << "�� ������� " << i << ": ";
        if (dist[i] == INF) {
            cout << "��� ����\n";
            continue;
        }
        cout << "���������� = " << dist[i] << ", ����: ";

        vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = prev[current];
        }
        reverse(path.begin(), path.end());

        for (size_t j = 0; j < path.size(); ++j) {
            if (j > 0) cout << " -> ";
            cout << path[j];
        }
        cout << endl;
    }
}
//�������� ��������
void deykstr(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    queue* head = NULL;
    queue* tail = NULL;
    push(head, tail, start, 0);

    while (head) {
        int u = pop(head, tail);
        if (visited[u]) continue;
        visited[u] = true;

        for (size_t i = 0; i < graph[u].size(); ++i) {
            int neighbor_vertex = graph[u][i].first;
            int edge_weight = graph[u][i].second;

            if (dist[u] != INF && dist[neighbor_vertex] > dist[u] + edge_weight) {
                dist[neighbor_vertex] = dist[u] + edge_weight;
                prev[neighbor_vertex] = u;
                push(head, tail, neighbor_vertex, dist[neighbor_vertex]);
            }
        }
    }

    printpaths(dist, prev, start);
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<vector<pair<int, int>>> graph = createlist();
    int start;
    cout << "������� ��������� �������: ";
    cin >> start;

    if (start >= graph.size()) {
        cout << "������: ��������� ������� ��� ���������\n";
        return 1;
    }
    deykstr(graph, start);
    return 0;
}