//���� ��������� �����.������� ���������� ���� ����� �� ������ � �� ������ �.
//������ ���� ������� ��� ������ � ����, ��������, �2 � �6.
//���� ������ ���� ������� � ���� ������ ������ �2 �4 �6 D8 E6
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct queue {
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

int pop(queue*& h, queue*& t) {
    queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

int cton(string pos) {//������� ��� �������������� ��������� ��������� � ����� 
    int col = toupper(pos[0]) - 'A';
    int row = pos[1] - '1';
    return row * 8 + col;
}

string ntoc(int num) {//������� ��� �������������� ����� � ��������� ����������
    char col = 'A' + (num % 8);
    char row = '1' + (num / 8);
    return string(1, col) + string(1, row);
}

//������� ��� ��������, ��������� �� ������ �� �����
bool isplace(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void bfs(int start, int end, vector<int>& dist, vector<int>& prev) {//����� � ������ ��� ������ ���� ����
    int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    queue* h = NULL, * t = NULL;
    dist[start] = 0;
    push(h, t, start);

    while (h) {
        int current = pop(h, t);
        if (current == end) break;

        int x = current % 8;
        int y = current / 8;

        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isplace(nx, ny)) {
                int neighbor = ny * 8 + nx;
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[current] + 1;
                    prev[neighbor] = current;
                    push(h, t, neighbor);
                }
            }
        }
    }
}

vector<int> findpath(int start, int end) {//������� ��� ������ ����������� ���� �����
    vector<int> dist(64, -1);
    vector<int> prev(64, -1);

    bfs(start, end, dist, prev);
    vector<int> path;
    for (int j = end; j != -1; j = prev[j]) {
        path.push_back(j);
    }
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    string startp, endp;
    cout << "start position: ";
    cin >> startp;
    cout << "end position: ";
    cin >> endp;

    int start = cton(startp);
    int end = cton(endp);

    vector<int> path = findpath(start, end);

    cout << "path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) cout << " ";
        cout << ntoc(path[i]);
    }
    cout << endl;

    return 0;
}