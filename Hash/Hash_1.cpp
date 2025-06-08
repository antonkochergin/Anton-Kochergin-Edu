// ����������� ����������� ���������
#include <iostream>  // ��� �����/������
#include <vector>    // ��� ������ � ������������� ���������
#include <string>    // ��� ������ �� ��������
#include <iomanip>   // ��� ���������������� ������
#include <fstream>   // ��� ������ � �������
using namespace std; // ������������� ������������ ������������ ����

// ���������� �������� �������
ifstream in("bazaeng.txt");  // ������� ���� � �������
ofstream out("b1.txt");      // �������� ���� (�� ������������ � ���� ���������)

// ��������� ��� �������� ����
struct date {
    int dd, mm, yy;  // ����, �����, ���
};

// ��������� ��� �������� ������ � ����������
struct people {
    string surname;   // �������
    string position;  // ���������
    date dob;         // ���� �������� (��������� date)
    int exp;          // ���� ������
    int salary;       // ��������
};

// ������� �������������� ������ ���� � ��������� date
date strdate(string str) {
    date x;
    string temp = str.substr(0, 2);  // ��������� ���� (������ 2 �������)
    x.dd = atoi(temp.c_str());       // ����������� ������ � �����
    temp = str.substr(3, 2);         // ��������� ����� (������� 3-4)
    x.mm = atoi(temp.c_str());       // ����������� ������ � �����
    temp = str.substr(6, 4);         // ��������� ��� (������� 6-9)
    x.yy = atoi(temp.c_str());       // ����������� ������ � �����
    return x;                        // ���������� ��������� date
}

// ������� ������ ������ �� �����
vector<people> inFile() {
    vector<people> x;  // ������ ��� �������� ������ � �����������
    people temp;       // ��������� ��������� ��� �������� ������ ������ ����������

    // ������ ������ �� ����� �� �����
    while (in >> temp.surname >> temp.position) {
        string tmp;
        in >> tmp;                   // ������ ���� ��� ������
        temp.dob = strdate(tmp);     // �������������� ������ � ����
        in >> temp.exp >> temp.salary; // ������ ����� � ��������
        x.push_back(temp);           // ���������� ���������� � ������
    }
    return x;  // ������� ������� � ������� ���� �����������
}

// ������� ������ ������ ������ ����������
void print(people x) {
    // ��������������� ����� ������:
    cout << setw(12) << left << x.surname;  // ������� (������ 12, ������������ �� ������ ����)
    cout << setw(15) << left << x.position; // ��������� (������ 15)

    // ��������������� ����� ���� � �������� ������
    if (x.dob.dd < 10) cout << left << '0' << x.dob.dd << '.';
    else cout << left << x.dob.dd << '.';
    if (x.dob.mm < 10) cout << '0' << x.dob.mm << '.';
    else cout << x.dob.mm << '.';

    cout << left << setw(6) << x.dob.yy;    // ���
    cout << setw(10) << left << x.exp;      // ����
    cout << setw(10) << left << x.salary << endl; // ��������
}

// ���-������� (����� ������� �� ������ ��������)
int hash_function(int month, int table_size) {
    return month % table_size;  // ������� �� ������� ������ �� ������ �������
}

// �������� ���-������� (�������� �����������)
void create_hash_table(vector<people>& data, vector<people>& hash_table, int table_size) {
    // ������������� ���-������� "�������" ����������
    hash_table.resize(table_size, { "", "", {0,0,0}, 0, 0 });

    // ���������� ���-������� �������
    for (size_t i = 0; i < data.size(); i++) {
        people& person = data[i];  // ������� ���������
        int index = hash_function(person.dob.mm, table_size); // ���������� ����

        // �������� ������������ ��� ���������� ��������
        int original_index = index;  // ���������� �������� ������
        bool placed = false;         // ���� ��������� ����������

        while (!placed) {
            // ���� ������ ����� - ��������� ����������
            if (hash_table[index].surname == "") {
                hash_table[index] = person;
                placed = true;
            }
            else {
                // ����� ��������� � ��������� ������ (� ������ ��������� ������)
                index = (index + 1) % table_size;

                // �������� �� ������������ �������
                if (index == original_index) {
                    cerr << "���-������� �����������!" << endl;
                    return;
                }
            }
        }
    }
}

// ����� ����������� �� ������ ��������
void search_by_month(vector<people>& hash_table, int month, int table_size) {
    int index = hash_function(month, table_size); // ���������� ����
    int original_index = index;                   // ���������� �������� ������
    bool found = false;                           // ���� ����������

    cout << "\n���������� ������ ��� ������ �������� " << month << ":\n";

    // ����� � ������ ��������� ��������
    while (true) {
        // ���� ����� ��������� - ������� ������
        if (hash_table[index].dob.mm == month) {
            print(hash_table[index]);
            found = true;
        }

        // ������� � ��������� ������
        index = (index + 1) % table_size;

        // ������� ������:
        // 1. ����� �� ������ ������
        // 2. ������ ������ ����
        if (hash_table[index].surname == "" || index == original_index) {
            break;
        }
    }

    // ���������, ���� ������ �� �������
    if (!found) {
        cout << "���������� � ������� �������� " << month << " �� �������.\n";
    }
}

// �������� ����������� �� ������ ��������
void delete_by_month(vector<people>& hash_table, int month, int table_size) {
    int index = hash_function(month, table_size); // ���������� ����
    int original_index = index;                   // ���������� �������� ������
    bool deleted = false;                         // ���� ��������

    while (true) {
        // ���� ����� ��������� - "�������" (�������� �� ������ ��������)
        if (hash_table[index].dob.mm == month) {
            hash_table[index] = { "", "", {0,0,0}, 0, 0 };
            deleted = true;
        }

        // ������� � ��������� ������
        index = (index + 1) % table_size;

        // ������� ������:
        // 1. ����� �� ������ ������
        // 2. ������ ������ ����
        if (hash_table[index].surname == "" || index == original_index) {
            break;
        }
    }

    // ��������� � ���������� ��������
    if (deleted) {
        cout << "��� ���������� � ������� �������� " << month << " �������.\n";
    }
    else {
        cout << "���������� � ������� �������� " << month << " �� �������.\n";
    }
}

// ����� ���-�������
void print_hash_table(vector<people>& hash_table, int table_size) {
    cout << "\n���-������� (���� - ����� ��������):\n";
    for (int i = 0; i < table_size; ++i) {
        cout << "[" << i << "]: ";  // ����� ������� ������

        // ����� ����������� ������
        if (hash_table[i].surname != "") {
            cout << hash_table[i].dob.mm << " (" << hash_table[i].surname << ")";
        }
        else {
            cout << "�����";  // ��� ������ �����
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");  // ��������� ������� ������

    // 1. ������ ������ �� �����
    vector<people> employees = inFile();

    // 2. ������������� ���-�������
    int table_size = 13;  // ������ ������� (������� ����� >12)
    vector<people> hash_table;

    // 3. �������� ���-�������
    create_hash_table(employees, hash_table, table_size);

    // 4. ����� ���-�������
    print_hash_table(hash_table, table_size);

    // 5. ������������ ������
    int month_to_search;
    cout << "\n������� ����� �������� ��� ������ (1-12): ";
    cin >> month_to_search;
    search_by_month(hash_table, month_to_search, table_size);

    // 6. ������������ ��������
    int month_to_delete;
    cout << "\n������� ����� �������� ��� �������� (1-12): ";
    cin >> month_to_delete;
    delete_by_month(hash_table, month_to_delete, table_size);

    // 7. ����� ����������� �������
    print_hash_table(hash_table, table_size);

    return 0;
}