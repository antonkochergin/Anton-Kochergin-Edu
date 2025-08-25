//2 ������ - ��� ������ ����� �����. ��������� ������ ��������� ������. ������� ��� �������� ������. ���� ����� ���, ������� ��������� �� ����
#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}
//������� ���� � ������ 
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) tr = n;
    else {
        tree* y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right) y = y->right;
                else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left) y = y->left;
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
            else {
                delete n;
                break;
            }
        }
    }
}

// ����������� ����� ������ � ���� �������� �������
void findOddLeaves(tree* tr, vector<int>& oddLeaves) {
    if (!tr) return;

    if (!tr->left && !tr->right) { // ���� ��� ����
        if (tr->inf % 2 != 0) {    // ���� �������� ��������
            oddLeaves.push_back(tr->inf);
        }
    }

    findOddLeaves(tr->left, oddLeaves);
    findOddLeaves(tr->right, oddLeaves);
}

int main() {
    tree* tr = NULL;
    int n, x;
    cout << "n: ";
    cin >> n;
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(tr, x);
    }

    vector<int> oddLeaves;
    findOddLeaves(tr, oddLeaves);

    if (oddLeaves.empty()) {
        cout << "No odd leaves found." << endl;
    }
    else {
        cout << "Odd leaves: ";
        for (int leaf : oddLeaves) {
            cout << leaf << " ";
        }
        cout << endl;
    }

    return 0;
}