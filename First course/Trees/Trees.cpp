//������ 1 - ��� ������ ����� �����. ��������� ������ ��������� ������. 
// ������� ���� �� ����� �� ���� �. 
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

//���������� ���������� ��� ������ � ��������
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};

//�������� ����, �������������� ���� ����� x, ��������� - NULL
tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

//������� �������� � ������ ��������� ������
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) tr = n; //���� ������ ������ - ������
    else {
        tree* y = tr;
        while (y) { //���� ���� ���������
            if (n->inf > y->inf) { //������ �����
                if (y->right) y = y->right;
                else {
                    n->parent = y; //���� ���������� ������ ��������
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { //����� �����
                if (y->left) y = y->left;
                else {
                    n->parent = y; //���� ���������� ����� ��������
                    y->left = n;
                    break;
                }
            }
            else { //���� ������� ��� ����������
                delete n;
                break;
            }
        }
    }
}

//����� �������� � ������ ��������� ������
tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr; //����� ��� ����� �� ����� �����
    //���� �������� ������
    if (x < tr->inf)
        return find(tr->left, x); //���� �� ����� �����
    else
        return find(tr->right, x); //���� �� ������ �����
}

//������� ��� ���������� ������ ������
//������ ���� - ������������ ����� ���� �� ���� �� �����
void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness; //��������� �������� ������� 
    if (x->left) max_height(x->left, max, deepness + 1); //���� ����� 
    if (x->right) max_height(x->right, max, deepness + 1); //���� ������ 
}

//������� �������� ������� �������
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Please increase the size of the terminal. Size now: "
            << szOfConsole.X << "x" << szOfConsole.Y
            << ". Minimum required: " << width << "x" << height << ".\n";
        return false;
    }
    return true;
}

//��������������� ������� ��� ������ ������
void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << right << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

//�������� ������� ������ ������
void printTree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max); //��������� ������ ������
        short width = 1 << (max + 1); //��������� ������ ��� ������
        short max_w = 128;
        if (width > max_w) width = max_w;
        //���� ���� ������ ������� ������ �� ���������� 
        while (!isSizeOfConsoleCorrect(width, max)) {
            system("pause");
        }

        //����������� ����� ��� ������
        for (short i = 0; i < max; ++i) cout << '\n';

        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        //������� ������
        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
    else {
        cout << "The tree is empty." << endl;
    }
}

//����� ���� �� ���� �� �����
void printpath(tree* node) {
    if (!node) return;

    //c������ ������� �� �����, ���������� �����
    int depth = 0;
    tree* current = node;
    while (current) {
        depth++;
        current = current->parent;
    }

    int* path = new int[depth]; //����� ��� �������� ���� 

    int count = 0;
    current = node;
    while (current) { //���������� �������� inf � ������ 
        path[count++] = current->inf;
        current = current->parent;
    }
    for (int i = count - 1; i >= 0; --i) {//������� ���� �� ����� � ����
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    delete[] path; //����������� ������
}

int main() {
    tree* tr = NULL;
    int n, x;
    cout << "n: ";
    cin >> n;
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(tr, x); //��������� �������� � ������
    }

    //�������� ������
    cout << endl << "the tree:" << endl;
    printTree(tr);

    cout << endl << "x: ";
    cin >> x;

    tree* target = find(tr, x); //���� ������� � ������
    if (!target) {
        cout << "node " << x << " not found in the tree" << endl;
    }
    else {
        cout << "path to " << x << ": ";
        printpath(target); //������� ���� � ��������
    }

    return 0;
}




















