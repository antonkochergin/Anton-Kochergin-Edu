
//ПОРАЗРЯДНАЯ
// #include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для получения максимального количества разрядов
int getMaxDigits(int num) {
    if (num == 0) return 1;
    return log10(num) + 1;
}

// Поразрядная сортировка (LSD) согласно алгоритму 19
void radixSortLSD(vector<int>& arr) {
    const int P = 10; // Основание системы счисления
    int max_num = *max_element(arr.begin(), arr.end());
    int k = getMaxDigits(max_num); // Максимальное количество разрядов

    vector<vector<int>> buckets(P); // P дополнительных векторов

    for (int i = 0; i < k; ++i) {
        // Распределение элементов по векторам
        for (int num : arr) {
            int digit = (num / (int)pow(P, i)) % P;
            buckets[digit].push_back(num);
        }

        // Перезапись векторов в массив
        int index = 0;
        for (int j = 0; j < P; ++j) {
            for (int num : buckets[j]) {
                arr[index++] = num;
            }
            buckets[j].clear(); // Очистка вектора
        }
    }
}

// Функции для работы с матрицей (чтение/запись)
vector<vector<int>> readMatrix(const string& filename, int& n) {
    ifstream in(filename);
    if (!in) {
        cerr << "Ошибка открытия файла " << filename << endl;
        exit(1);
    }

    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
    in.close();
    return matrix;
}

void writeMatrix(const string& filename, const vector<vector<int>>& matrix) {
    ofstream out(filename);
    if (!out) {
        cerr << "Ошибка создания файла " << filename << endl;
        exit(1);
    }

    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
    out.close();
}

// Сортировка матрицы
void sortMatrix(vector<vector<int>>& matrix) {
    // Преобразование матрицы в одномерный массив
    vector<int> flat;
    for (const auto& row : matrix) {
        flat.insert(flat.end(), row.begin(), row.end());
    }

    // Сортировка
    radixSortLSD(flat);

    // Восстановление матрицы
    int idx = 0;
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = flat[idx++];
        }
    }
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    int n;

    // Чтение матрицы
    auto matrix = readMatrix(inputFile, n);

    // Сортировка
    sortMatrix(matrix);

    // Запись результата
    writeMatrix(outputFile, matrix);

    return 0;
}
//
// 
// 
// 
// 
// 
// 
// ШЕЛЛА С ШАГОМ 3
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функция для считывания матрицы из файла
vector<vector<int>> readMatrix(const string& filename, int& n) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Ошибка открытия файла " << filename << endl;
        exit(1);
    }

    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
    in.close();
    return matrix;
}

// Функция для записи матрицы в файл
void writeMatrix(const string& filename, const vector<vector<int>>& matrix) {
    ofstream out(filename);
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
    out.close();
}

// Точная реализация алгоритма 10 (сортировка Шелла с шагом 3)
void shellSort(vector<int>& arr) {
    int n = arr.size();
    int step = n / 3; // Начальный шаг

    while (step >= 1) {
        for (int i = 0; i < n - step; ++i) {
            int j = i;
            while (j >= 0 && arr[j] > arr[j + step]) {
                swap(arr[j], arr[j + step]);
                j -= step;
            }
        }
        step /= 3; // Уменьшаем шаг
        if (step == 0) step = 1; // Гарантируем последний проход с шагом 1
    }
}

// Сортировка матрицы
void sortMatrix(vector<vector<int>>& matrix) {
    // Преобразуем матрицу в одномерный массив
    vector<int> flat;
    int n = matrix.size();
    for (const auto& row : matrix) {
        flat.insert(flat.end(), row.begin(), row.end());
    }
    // Сортируем
    shellSort(flat);
    // Восстанавливаем матрицу
    int idx = 0;
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = flat[idx++];
        }
    }
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    int n;

    // Чтение
    auto matrix = readMatrix(inputFile, n);

    // Сортировка
    sortMatrix(matrix);

    // Запись
    writeMatrix(outputFile, matrix);
    return 0;
}
//
//
//
// 
// 
// 
// 
// 
// 
//ВЫБОРОМ
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Устойчивая сортировка выбором (Алгоритм 12)
void stableSelectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        // Находим минимальный элемент в неотсортированной части
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Вставляем минимальный элемент на i-ю позицию (со сдвигом)
        int min_val = arr[min_idx];
        for (int k = min_idx; k > i; --k) {
            arr[k] = arr[k - 1];
        }
        arr[i] = min_val;
    }
}
vector<vector<int>> readMatrix(const string& filename, int& n) {
    ifstream in(filename);
    if (!in) {
        exit(1);
    }

    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
    in.close();
    return matrix;
}

void writeMatrix(const string& filename, const vector<vector<int>>& matrix) {
    ofstream out(filename);
    if (!out) {
        cerr << "Ошибка создания файла " << filename << endl;
        exit(1);
    }

    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
    out.close();
}

void sortMatrix(vector<vector<int>>& matrix) {
    // Преобразование матрицы в одномерный массив
    vector<int> flat;
    for (const auto& row : matrix) {
        flat.insert(flat.end(), row.begin(), row.end());
    }

    //сортировка
    stableSelectionSort(flat);
    //восстановление матрицы
    int idx = 0;
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = flat[idx++];
        }
    }
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    int n;

    // Чтение матрицы
    auto matrix = readMatrix(inputFile, n);

    // Выбор типа сортировки

    // Сортировка
    sortMatrix(matrix);

    // Запись результата
    writeMatrix(outputFile, matrix);
    return 0;
}
