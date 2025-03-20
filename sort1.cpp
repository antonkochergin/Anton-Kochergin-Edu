#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ��������� ��� �������� ������ � ����������
struct Employee {
    string surname;
    string position;
    int birthDay, birthMonth, birthYear;
    int experience;
    double salary;
};

// ������������� ���������� ��� ������ �5 (�� ���������)
void heapify(vector<Employee>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].position > arr[largest].position)
        largest = left;

    if (right < n && arr[right].position > arr[largest].position)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<Employee>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ������ ���������� ��� ������ �10 (�� ��������� � ��������)
void gnomeSort(vector<Employee>& arr) {
    int n = arr.size();
    int index = 0;

    while (index < n) {
        if (index == 0 || (arr[index].position >= arr[index - 1].position &&
            (arr[index].position != arr[index - 1].position || arr[index].salary >= arr[index - 1].salary))) {
            index++;
        }
        else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}

// ��������� ���������� ��� ������ �13 (�� ���� ��������)
void shakerSort(vector<Employee>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;

        // ������ ����� �������
        for (int i = left; i < right; i++) {
            if (arr[i].birthYear > arr[i + 1].birthYear ||
                (arr[i].birthYear == arr[i + 1].birthYear && arr[i].birthMonth > arr[i + 1].birthMonth) ||
                (arr[i].birthYear == arr[i + 1].birthYear && arr[i].birthMonth == arr[i + 1].birthMonth && arr[i].birthDay > arr[i + 1].birthDay)) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        right--;

        // ������ ������ ������
        for (int i = right; i > left; i--) {
            if (arr[i - 1].birthYear > arr[i].birthYear ||
                (arr[i - 1].birthYear == arr[i].birthYear && arr[i - 1].birthMonth > arr[i].birthMonth) ||
                (arr[i - 1].birthYear == arr[i].birthYear && arr[i - 1].birthMonth == arr[i].birthMonth && arr[i - 1].birthDay > arr[i].birthDay)) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        left++;
    }
}

// ������� ��� ������ ������ � ����������� �� �����
vector<Employee> readEmployees(const string& filename) {
    ifstream file(filename);
    vector<Employee> employees;
    string line;

    while (getline(file, line)) {
        Employee emp;
        size_t pos = 0;
        size_t prev = 0;
        string token;
        vector<string> tokens;

        // ���������� ������ �� ", "
        while ((pos = line.find(", ", prev)) != string::npos) {
            token = line.substr(prev, pos - prev);
            tokens.push_back(token);
            prev = pos + 2;
        }
        tokens.push_back(line.substr(prev));

        // ���������� ��������� Employee
        emp.surname = tokens[0];
        emp.position = tokens[1];
        emp.birthDay = stoi(tokens[2].substr(0, 2));
        emp.birthMonth = stoi(tokens[2].substr(3, 2));
        emp.birthYear = stoi(tokens[2].substr(6, 4));
        emp.experience = stoi(tokens[3]);
        emp.salary = stod(tokens[4]);

        employees.push_back(emp);
    }

    return employees;
}

// ������� ��� ������ ��������������� ������ � ����
void writeEmployees(const string& filename, const vector<Employee>& employees) {
    ofstream file(filename);
    for (const auto& emp : employees) {
        file << emp.surname << ", " << emp.position << ", "
            << emp.birthDay << "." << emp.birthMonth << "." << emp.birthYear << ", "
            << emp.experience << ", " << emp.salary << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    // ������ ������ �� �����
    vector<Employee> employees = readEmployees("employees.txt");

    // ������ �5: ���������� �� ��������� (������������� ����������)
    vector<Employee> task5 = employees;
    heapSort(task5);
    writeEmployees("task5_sorted.txt", task5);

    // ������ �10: ���������� �� ��������� � �������� (������ ����������)
    vector<Employee> task10 = employees;
    gnomeSort(task10);
    writeEmployees("task10_sorted.txt", task10);

    // ������ �13: ���������� �� ���� �������� (��������� ����������)
    vector<Employee> task13 = employees;
    shakerSort(task13);
    writeEmployees("task13_sorted.txt", task13);

    cout << "- task5_sorted.txt (�� ���������)" << endl;
    cout << "- task10_sorted.txt (�� ��������� � ��������)" << endl;
    cout << "- task13_sorted.txt (�� ���� ��������)" << endl;

    return 0;
}