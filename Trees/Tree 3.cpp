////3 задача - Дан список целых чисел. Построить дерево бинарного поиска. 
//Удалить среднюю по значению вершину, расположенную на уровне К. Нумерация уровней начинается с нуля, К >=2.
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

// Найти все узлы на уровне K
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

// Найти минимальный узел в поддереве (для удаления)
tree* findMin(tree* tr) {
    while (tr->left) tr = tr->left;
    return tr;
}

// Удаление узла из BST
tree* deleteNode(tree* tr, int x) {
    if (!tr) return tr;

    if (x < tr->inf) { //переходим в левую ветку 
        tr->left = deleteNode(tr->left, x);
    }
    else if (x > tr->inf) { //переходим в правую ветку
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
        // Сортируем узлы по значению
        vector<int> values;
        for (tree* node : nodesAtLevelK) {
            values.push_back(node->inf);
        }
        sort(values.begin(), values.end());

        // Выбираем медиану (средний элемент)
        int median = values[values.size() / 2];
        cout << "Median node at level " << K << ": " << median << endl;

        // Удаляем узел
        tr = deleteNode(tr, median);
        cout << "Tree after deletion:" << endl;
        // (Здесь можно добавить вывод дерева, если нужно)
    }

    return 0;
}