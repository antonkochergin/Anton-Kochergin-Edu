//1

////��� ����� ����� �����. ������� ��������� ����������� �����.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> a = {};
    int n;
    cout << "n = ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = ";
        int x;
        cin >> x;
        a.push_back(x);
    }

    auto miter = min_element(a.begin(), a.end());

    auto last_min_iter = a.end();
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (*it == *miter) {
            last_min_iter = it;
        }
    }
    if (last_min_iter != a.end()) {
        a.erase(last_min_iter);
    }

    for (int num : a) {
        cout << num << " ";
    }

    return 0;
}

//2

//���� 2 ������������������ ����� �����.  ������� �� ������ ������������������ ��� �������� �����.
// �������� �� ������ ������������������ ��� �����, ������� �, ������������ ������. ������������� ��� ������������������.
// ��������� �� � ���� ��������������� ������������������ (����������� ��������. �������� ���� ������������������ � ����� �
// ����� ������������� - �� �������� ����������� ��������). �������� ����� ������� ���, ����� ������������������ �������� ���������������.
// (����������� ��������.  ��������  � ����� � ����� ������������� - �� �������� ����������� ��������).
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void remove(vector<int>& vec) {
    vec.erase(remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 != 0; }), vec.end());
}

void replace(vector<int>& vec, int X) {
    if (vec.empty()) return;
    int max_val = *max_element(vec.begin(), vec.end());
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it % X == 0) {
            *it = max_val;
        }
    }
}

vector<int> msorted(const vector<int>& seq1, const vector<int>& seq2) {
    vector<int> merged(seq1.size() + seq2.size()); // �������� ������ �������
    merge(seq1.begin(), seq1.end(), seq2.begin(), seq2.end(), merged.begin());
    return merged;
}

//������� ��. � ���������������� ������������������ 
void isorted(vector<int>& seq, int value) {
    auto it = seq.begin();
    while (it != seq.end() && *it < value) {
        ++it;
    }
    seq.insert(it, value);
}

int main() {
    int n1;
    cout << "len A = ";
    cin >> n1;
    int n2;
    cout << "len B = ";
    cin >> n2;
    vector <int> a = {};
    vector <int> b = {};
    for (int i = 0; i < n1; i++) {
        cout << "a[" << i << "] = ";
        int x;
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < n2; i++) {
        cout << "a[" << i << "] = ";
        int x;
        cin >> x;
        b.push_back(x);
    }
    int x ;  
    cout << " x = ";
    cin >> x;
    int ne ;
    cout << "New element = ";
    cin >> ne;

//�������� 
    remove(a);
//������
    replace(b, x);

//����������
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

//�����������
    vector<int> c = msorted(a, b);

//�������
    isorted(c, ne);

//�����
    for (auto it = c.begin(); it != c.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}

//3

//��������� ���������� numeric � functional, ����� ������ n  �������� 2.
#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

int main() {
    int n;
    cout << "������� ���������� ��������: ";
    cin >> n;

    vector<int> a(n);
    iota(a.begin(), a.end(), 0); // ������� 

    transform(a.begin(), a.end(), a.begin(), [](int x) {return static_cast<int>(pow(2, x));}); //�������� � �������

    for (int num : a) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
