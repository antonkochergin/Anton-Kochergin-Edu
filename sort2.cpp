#include <iostream>
#include <vector>

using namespace std;

// Функция для преобразования поддерева с корнем в i в кучу
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Функция для построения кучи
void buildHeap(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

// Сортировка выбором
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);

        // Вывод массива после каждой итерации
        cout << "Iteration " << i + 1 << ": ";
        printArray(arr);
    }
}

// Сортировка вставками
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;

        // Вывод массива после каждой итерации
        cout << "Iteration " << i << ": ";
        printArray(arr);
    }
}

int main() {
    vector<int> arr = { 3, 5, 8, 10, 17, 11, 13, 19, 22 };
    int n = arr.size();

    // Построение кучи
    buildHeap(arr, n);
    printArray(arr);

    // Сортировка выбором
    vector<int> arrSelection = arr;
    selectionSort(arrSelection);

    // Сортировка вставками
    vector<int> arrInsertion = arr;
    insertionSort(arrInsertion);

    return 0;
}