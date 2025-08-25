////3 ������ - ��� ������ ����� �����. ��������� ������ ��������� ������. 
//������� ������� �� �������� �������, ������������� �� ������ �. ��������� ������� ���������� � ����, � >=2.
#include <iostream>
#include <vector>
#include <algorithm>
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

// ����� ��� ���� �� ������ K
void findNodesAtLevel(tree* tr, int currentLevel, int targetLevel, vector<tree*>& nodes) {
    if (!tr) return;

    if (currentLevel == targetLevel) {
        nodes.push_back(tr);
    }
    else if (currentLevel < targetLevel) {
        findNodesAtLevel(tr->left, currentLevel + 1, targetLevel, nodes);
        findNodesAtLevel(tr->right, currentLevel + 1, targetLevel, nodes);
    }
}

// ����� ����������� ���� � ��������� (��� ��������)
tree* findMin(tree* tr) {
    while (tr->left) tr = tr->left;
    return tr;
}

// �������� ���� �� BST
tree* deleteNode(tree* tr, int x) {
    if (!tr) return tr;

    if (x < tr->inf) { //��������� � ����� ����� 
        tr->left = deleteNode(tr->left, x);
    }
    else if (x > tr->inf) { //��������� � ������ �����
        tr->right = deleteNode(tr->right, x);
    }
    else {
        if (!tr->left) {
            tree* temp = tr->right;
            delete tr;
            return temp;
        }
        else if (!tr->right) {
            tree* temp = tr->left;
            delete tr;
            return temp;
        }

        tree* temp = findMin(tr->right);
        tr->inf = temp->inf;
        tr->right = deleteNode(tr->right, temp->inf);
    }
    return tr;
}

int main() {
    tree* tr = NULL;
    int n, x, K;
    cout << "n: ";
    cin >> n;
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(tr, x);
    }

    cout << "Enter K (>=2): ";
    cin >> K;
    if (K < 2) {
        cout << "K must be >= 2." << endl;
        return 0;
    }

    vector<tree*> nodesAtLevelK;
    findNodesAtLevel(tr, 0, K, nodesAtLevelK);

    if (nodesAtLevelK.empty()) {
        cout << "No nodes at level " << K << "." << endl;
    }
    else {
        // ��������� ���� �� ��������
        vector<int> values;
        for (tree* node : nodesAtLevelK) {
            values.push_back(node->inf);
        }
        sort(values.begin(), values.end());

        // �������� ������� (������� �������)
        int median = values[values.size() / 2];
        cout << "Median node at level " << K << ": " << median << endl;

        // ������� ����
        tr = deleteNode(tr, median);
        cout << "Tree after deletion:" << endl;
        // (����� ����� �������� ����� ������, ���� �����)
    }

    return 0;
}