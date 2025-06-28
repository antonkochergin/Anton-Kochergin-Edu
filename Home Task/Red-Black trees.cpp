#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

#define RED true
#define BLACK false

struct TreeNode {
    int value;
    bool color; // RED или BLACK
    TreeNode* leftChild, * rightChild, * parent;

    TreeNode(int val, bool col = RED, TreeNode* p = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr)
        : value(val), color(col), parent(p), leftChild(left), rightChild(right) {}
};

TreeNode* treeRoot = nullptr;

void CalculateMaxDepth(TreeNode* node, short& maxDepth, short currentDepth = 1) {
    if (currentDepth > maxDepth) maxDepth = currentDepth;
    if (node->leftChild) CalculateMaxDepth(node->leftChild, maxDepth, currentDepth + 1);
    if (node->rightChild) CalculateMaxDepth(node->rightChild, maxDepth, currentDepth + 1);
}

void VisualizeTree(TreeNode* node, COORD position, short offset) {
    SetConsoleTextAttribute(consoleHandle, node->color == RED ? 12 : 8);
    SetConsoleCursorPosition(consoleHandle, position);
    cout << setw(offset + 1) << node->value;

    if (node->leftChild) VisualizeTree(node->leftChild, { position.X, short(position.Y + 1) }, offset >> 1);
    if (node->rightChild) VisualizeTree(node->rightChild, { short(position.X + offset), short(position.Y + 1) }, offset >> 1);
}

void DisplayTree() {
    if (!treeRoot) return;

    short treeHeight = 1;
    CalculateMaxDepth(treeRoot, treeHeight);

    short treeWidth = 1 << (treeHeight + 1);
    const short maxWidth = 128;
    if (treeWidth > maxWidth) treeWidth = maxWidth;

    for (short i = 0; i < treeHeight; ++i) cout << '\n';

    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    COORD endPosition = consoleInfo.dwCursorPosition;

    VisualizeTree(treeRoot, { 0, short(endPosition.Y - treeHeight) }, treeWidth >> 1);

    SetConsoleCursorPosition(consoleHandle, endPosition);
    SetConsoleTextAttribute(consoleHandle, 7);
}

void RotateLeft(TreeNode* pivotNode) {
    TreeNode* rightChild = pivotNode->rightChild;
    pivotNode->rightChild = rightChild->leftChild;
    if (rightChild->leftChild != nullptr) {
        rightChild->leftChild->parent = pivotNode;
    }
    rightChild->parent = pivotNode->parent;
    if (pivotNode->parent == nullptr) {
        treeRoot = rightChild;
    }
    else if (pivotNode == pivotNode->parent->leftChild) {
        pivotNode->parent->leftChild = rightChild;
    }
    else {
        pivotNode->parent->rightChild = rightChild;
    }
    rightChild->leftChild = pivotNode;
    pivotNode->parent = rightChild;
}

void RotateRight(TreeNode* pivotNode) {
    TreeNode* leftChild = pivotNode->leftChild;
    pivotNode->leftChild = leftChild->rightChild;
    if (leftChild->rightChild != nullptr) {
        leftChild->rightChild->parent = pivotNode;
    }
    leftChild->parent = pivotNode->parent;
    if (pivotNode->parent == nullptr) {
        treeRoot = leftChild;
    }
    else if (pivotNode == pivotNode->parent->rightChild) {
        pivotNode->parent->rightChild = leftChild;
    }
    else {
        pivotNode->parent->leftChild = leftChild;
    }
    leftChild->rightChild = pivotNode;
    pivotNode->parent = leftChild;
}

void FixInsertion(TreeNode* newNode) {
    while (newNode->parent != nullptr && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->rightChild) {
            TreeNode* uncle = newNode->parent->parent->leftChild;
            if (uncle != nullptr && uncle->color == RED) {
                uncle->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else {
                if (newNode == newNode->parent->leftChild) {
                    newNode = newNode->parent;
                    RotateRight(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                RotateLeft(newNode->parent->parent);
            }
        }
        else {
            TreeNode* uncle = newNode->parent->parent->rightChild;
            if (uncle != nullptr && uncle->color == RED) {
                uncle->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else {
                if (newNode == newNode->parent->rightChild) {
                    newNode = newNode->parent;
                    RotateLeft(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                RotateRight(newNode->parent->parent);
            }
        }
        if (newNode == treeRoot) break;
    }
    treeRoot->color = BLACK;
}

void InsertValue(int value) {
    TreeNode* newNode = new TreeNode(value);
    TreeNode* parentNode = nullptr;
    TreeNode* currentNode = treeRoot;

    while (currentNode) {
        parentNode = currentNode;
        if (newNode->value < currentNode->value) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }

    newNode->parent = parentNode;
    if (parentNode == nullptr) {
        treeRoot = newNode;
    }
    else if (newNode->value < parentNode->value) {
        parentNode->leftChild = newNode;
    }
    else {
        parentNode->rightChild = newNode;
    }

    if (newNode->parent == nullptr) {
        newNode->color = BLACK;
        return;
    }
    if (newNode->parent->parent == nullptr) return;

    FixInsertion(newNode);
}

void InOrderTraversal(TreeNode* node) {
    if (node != nullptr) {
        InOrderTraversal(node->leftChild);
        cout << node->value << " ";
        InOrderTraversal(node->rightChild);
    }
}

vector<int> FindPathToNode(int targetValue) {
    vector<int> path;
    TreeNode* currentNode = treeRoot;
    while (currentNode) {
        path.push_back(currentNode->value);
        if (targetValue == currentNode->value) {
            return path;
        }
        else if (targetValue < currentNode->value) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }
    return vector<int>();
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<int> valuesToInsert = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };

    for (int value : valuesToInsert) {
        InsertValue(value);
    }

    cout << "Визуализация дерева: " << endl;
    DisplayTree();
    cout << endl;

    cout << "Симметричный обход: ";
    InOrderTraversal(treeRoot);
    cout << endl;

    cout << "Визуализация дерева: " << endl;
    DisplayTree();
    cout << endl;

    int targetNodeValue = 13;
    vector<int> path = FindPathToNode(targetNodeValue);
    if (!path.empty()) {
        cout << "Путь до " << targetNodeValue << ": ";
        for (int nodeValue : path) {
            cout << " -> " << nodeValue;
        }
        cout << endl;
    }
    else {
        cout << "Узел не найден!" << endl;
    }

    return 0;
}