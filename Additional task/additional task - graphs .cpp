//���� ����������� � ���� ������ ���������. 
//����������� ����� � ������, ��������� �������, � ������������� ����� � �������.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct queue {//��������� �������
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) {//������� ���������� �������� � �������
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

int pop(queue*& h, queue*& t) {//������� �������� �������� �� �������
    queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

struct stack {//��������� �����
    int inf;
    stack* next;
};

void push(stack*& h, int x) {//������� ���������� �������� � ����
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack*& h) {//������� �������� �������� �� �����
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

void bfs(vector<vector<int>>& Gr, int N, int x) {//������� ������ � ������ 
    queue* h = NULL, * t = NULL;
    vector<int> a(N, 0);

    a[x] = 1;
    push(h, t, x);
    cout << x << " ";

    while (h) {
        int current = pop(h, t);

        for (size_t i = 0; i < Gr[current].size(); ++i) {
            int neighbor = Gr[current][i];
            if (a[neighbor] == 0) {
                a[neighbor] = 1;
                push(h, t, neighbor);
                cout << neighbor << " ";
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (a[i] == 0) {
            bfs(Gr, N, i);
        }
    }
}

void dfs(vector<vector<int>>& Gr, int N, int x) {//������� ������ � �������
    stack* h = NULL;
    vector<int> a(N, 0);

    a[x] = 1;
    push(h, x);
    cout << x << " ";

    while (h) {
        int current = h->inf;
        bool found = false;

        for (size_t i = 0; i < Gr[current].size(); ++i) {
            int neighbor = Gr[current][i];
            if (a[neighbor] == 0) {
                a[neighbor] = 1;
                push(h, neighbor);
                cout << neighbor << " ";
                found = true;
                break;
            }
        }

        if (!found) {
            pop(h);
        }
    }
    for (int i = 0; i < N; ++i) {
        if (a[i] == 0) {
            dfs(Gr, N, i);
        }
    }
}


vector<int> parse(string& line) {
    vector<int> numbers;
    string n;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == ' ') {
            if (!n.empty()) {
                numbers.push_back(stoi(n));
                n.clear();
            }
        }
        else {
            n += c;
        }
    }
    if (!n.empty()) {
        numbers.push_back(stoi(n));
    }
    return numbers;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int N;
    cout << "���������� ������ �����: ";
    cin >> N;
    cin.ignore();
    vector<vector<int>> Gr(N);

    cout << "������ ��������� ����� ������:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "������� " << i << ": ";
        string line;
        getline(cin, line);
        vector<int> neighbors = parse(line);

        Gr[i] = neighbors;
    }
    int start;
    cout << "��������� ������� ��� ������: ";
    cin >> start;
    cout << "��������� ������ � ������: ";
    bfs(Gr, N, start);
    cout << endl;
    cout << "��������� ������ � �������: ";
    dfs(Gr, N, start);
    cout << endl;

    return 0;
}