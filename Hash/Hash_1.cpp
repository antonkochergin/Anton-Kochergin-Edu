// Подключение необходимых библиотек
#include <iostream>  // Для ввода/вывода
#include <vector>    // Для работы с динамическими массивами
#include <string>    // Для работы со строками
#include <iomanip>   // Для форматированного вывода
#include <fstream>   // Для работы с файлами
using namespace std; // Использование стандартного пространства имен

// Объявление файловых потоков
ifstream in("bazaeng.txt");  // Входной файл с данными
ofstream out("b1.txt");      // Выходной файл (не используется в этой программе)

// Структура для хранения даты
struct date {
    int dd, mm, yy;  // День, месяц, год
};

// Структура для хранения данных о сотруднике
struct people {
    string surname;   // Фамилия
    string position;  // Должность
    date dob;         // Дата рождения (структура date)
    int exp;          // Стаж работы
    int salary;       // Зарплата
};

// Функция преобразования строки даты в структуру date
date strdate(string str) {
    date x;
    string temp = str.substr(0, 2);  // Извлекаем день (первые 2 символа)
    x.dd = atoi(temp.c_str());       // Преобразуем строку в число
    temp = str.substr(3, 2);         // Извлекаем месяц (символы 3-4)
    x.mm = atoi(temp.c_str());       // Преобразуем строку в число
    temp = str.substr(6, 4);         // Извлекаем год (символы 6-9)
    x.yy = atoi(temp.c_str());       // Преобразуем строку в число
    return x;                        // Возвращаем структуру date
}

// Функция чтения данных из файла
vector<people> inFile() {
    vector<people> x;  // Вектор для хранения данных о сотрудниках
    people temp;       // Временная структура для хранения данных одного сотрудника

    // Чтение данных из файла до конца
    while (in >> temp.surname >> temp.position) {
        string tmp;
        in >> tmp;                   // Чтение даты как строки
        temp.dob = strdate(tmp);     // Преобразование строки в дату
        in >> temp.exp >> temp.salary; // Чтение стажа и зарплаты
        x.push_back(temp);           // Добавление сотрудника в вектор
    }
    return x;  // Возврат вектора с данными всех сотрудников
}

// Функция печати данных одного сотрудника
void print(people x) {
    // Форматированный вывод данных:
    cout << setw(12) << left << x.surname;  // Фамилия (ширина 12, выравнивание по левому краю)
    cout << setw(15) << left << x.position; // Должность (ширина 15)

    // Форматированный вывод даты с ведущими нулями
    if (x.dob.dd < 10) cout << left << '0' << x.dob.dd << '.';
    else cout << left << x.dob.dd << '.';
    if (x.dob.mm < 10) cout << '0' << x.dob.mm << '.';
    else cout << x.dob.mm << '.';

    cout << left << setw(6) << x.dob.yy;    // Год
    cout << setw(10) << left << x.exp;      // Стаж
    cout << setw(10) << left << x.salary << endl; // Зарплата
}

// Хэш-функция (метод деления по месяцу рождения)
int hash_function(int month, int table_size) {
    return month % table_size;  // Остаток от деления месяца на размер таблицы
}

// Создание хэш-таблицы (закрытое хэширование)
void create_hash_table(vector<people>& data, vector<people>& hash_table, int table_size) {
    // Инициализация хэш-таблицы "пустыми" значениями
    hash_table.resize(table_size, { "", "", {0,0,0}, 0, 0 });

    // Заполнение хэш-таблицы данными
    for (size_t i = 0; i < data.size(); i++) {
        people& person = data[i];  // Текущий сотрудник
        int index = hash_function(person.dob.mm, table_size); // Вычисление хэша

        // Линейное пробирование для разрешения коллизий
        int original_index = index;  // Запоминаем исходный индекс
        bool placed = false;         // Флаг успешного размещения

        while (!placed) {
            // Если ячейка пуста - размещаем сотрудника
            if (hash_table[index].surname == "") {
                hash_table[index] = person;
                placed = true;
            }
            else {
                // Иначе переходим к следующей ячейке (с учетом кругового буфера)
                index = (index + 1) % table_size;

                // Проверка на переполнение таблицы
                if (index == original_index) {
                    cerr << "Хэш-таблица переполнена!" << endl;
                    return;
                }
            }
        }
    }
}

// Поиск сотрудников по месяцу рождения
void search_by_month(vector<people>& hash_table, int month, int table_size) {
    int index = hash_function(month, table_size); // Вычисление хэша
    int original_index = index;                   // Запоминаем исходный индекс
    bool found = false;                           // Флаг нахождения

    cout << "\nРезультаты поиска для месяца рождения " << month << ":\n";

    // Поиск с учетом возможных коллизий
    while (true) {
        // Если месяц совпадает - выводим данные
        if (hash_table[index].dob.mm == month) {
            print(hash_table[index]);
            found = true;
        }

        // Переход к следующей ячейке
        index = (index + 1) % table_size;

        // Условия выхода:
        // 1. Дошли до пустой ячейки
        // 2. Прошли полный круг
        if (hash_table[index].surname == "" || index == original_index) {
            break;
        }
    }

    // Сообщение, если ничего не найдено
    if (!found) {
        cout << "Сотрудники с месяцем рождения " << month << " не найдены.\n";
    }
}

// Удаление сотрудников по месяцу рождения
void delete_by_month(vector<people>& hash_table, int month, int table_size) {
    int index = hash_function(month, table_size); // Вычисление хэша
    int original_index = index;                   // Запоминаем исходный индекс
    bool deleted = false;                         // Флаг удаления

    while (true) {
        // Если месяц совпадает - "удаляем" (заменяем на пустое значение)
        if (hash_table[index].dob.mm == month) {
            hash_table[index] = { "", "", {0,0,0}, 0, 0 };
            deleted = true;
        }

        // Переход к следующей ячейке
        index = (index + 1) % table_size;

        // Условия выхода:
        // 1. Дошли до пустой ячейки
        // 2. Прошли полный круг
        if (hash_table[index].surname == "" || index == original_index) {
            break;
        }
    }

    // Сообщение о результате удаления
    if (deleted) {
        cout << "Все сотрудники с месяцем рождения " << month << " удалены.\n";
    }
    else {
        cout << "Сотрудники с месяцем рождения " << month << " не найдены.\n";
    }
}

// Вывод хэш-таблицы
void print_hash_table(vector<people>& hash_table, int table_size) {
    cout << "\nХэш-таблица (ключ - месяц рождения):\n";
    for (int i = 0; i < table_size; ++i) {
        cout << "[" << i << "]: ";  // Вывод индекса ячейки

        // Вывод содержимого ячейки
        if (hash_table[i].surname != "") {
            cout << hash_table[i].dob.mm << " (" << hash_table[i].surname << ")";
        }
        else {
            cout << "Пусто";  // Для пустых ячеек
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");  // Установка русской локали

    // 1. Чтение данных из файла
    vector<people> employees = inFile();

    // 2. Инициализация хэш-таблицы
    int table_size = 13;  // Размер таблицы (простое число >12)
    vector<people> hash_table;

    // 3. Создание хэш-таблицы
    create_hash_table(employees, hash_table, table_size);

    // 4. Вывод хэш-таблицы
    print_hash_table(hash_table, table_size);

    // 5. Демонстрация поиска
    int month_to_search;
    cout << "\nВведите месяц рождения для поиска (1-12): ";
    cin >> month_to_search;
    search_by_month(hash_table, month_to_search, table_size);

    // 6. Демонстрация удаления
    int month_to_delete;
    cout << "\nВведите месяц рождения для удаления (1-12): ";
    cin >> month_to_delete;
    delete_by_month(hash_table, month_to_delete, table_size);

    // 7. Вывод обновленной таблицы
    print_hash_table(hash_table, table_size);

    return 0;
}