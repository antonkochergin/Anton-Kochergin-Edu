//1
#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

set<int> notfind(const vector<int>& numbers) {
    set<int> Digits;
    set<int> ThreeDigits;

    for (int num : numbers) {
        int n = num;
        //извлекаем цифры 
        while (n > 0) {
            int digit = n % 10; 
            Digits.insert(digit);
            n /= 10; 
        }

        //если число трехзначно, то отдельно его обрабатываем 
        if (num >= 100 && num <= 999) {
            n = num; 
            //извлекаем цифры
            while (n > 0) {
                int digit = n % 10; 
                ThreeDigits.insert(digit); 
                n /= 10;
            }
        }
    }

    //результат
    set<int> result;
    //проверяем на совпадение
    for (int digit : Digits) {
        if (ThreeDigits.find(digit) == ThreeDigits.end()) {
            result.insert(digit);
        }
    }

    return result;
}

int main() {
    vector<int> numbers = { 123, 456, 789, 12, 34, 56, 78, 90, 111, 222, 333, 444, 555, 666, 777, 888, 999, 1000 };
    set<int> NonThreeDigit = notfind(numbers);
    for (int digit : NonThreeDigit) {
        cout << digit << " ";
    }
    cout << endl;

    return 0;
}






//2
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main() {
    //файл
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Err" << endl;
        return 1;
    }

    //читаем данные в одну строку 
    string line;
    getline(inputFile, line);
    inputFile.close();

    // строковый поток для разбиения данных на элементы
    stringstream ss(line);
    string el;
    vector<string> els; // вектор для хранения элементов
    //(item , count)
    map<int, int> numberCounts; // словарь для подсчета количества вхождений 
    string firstWord; // первое слово
    bool isFirstWord = true; // флаг для определения первого слова



    // Разбиваем строку на элементы
    while (ss >> el) {
        els.push_back(el);

        // если элемент - число, добавляем его в словарь
        try {
            int number = stoi(el); // пытаемся преобразовать элемент в число
            numberCounts[number]++; // увеличиваем счетчик для этого числа
        }
        catch (invalid_argument&) {
            // если элемент не число , то оно - слово
            if (isFirstWord) {
                firstWord = el; // запоминаем первое слово
                isFirstWord = false;
            }
        }
    }



    // сколько раз встречается первое слово - проход по всем 
    int firstWordCount = 0;
    for (const string& t : els) {
        if (t == firstWord) {
            firstWordCount++;
        }
    }

    // находим все числа, которые встречаются столько же раз, сколько первое слово - проход по числам 
    set<int> resultNumbers; //результат
    for (const auto& pair : numberCounts) {
        if (pair.second == firstWordCount) {
            resultNumbers.insert(pair.first); 
        }
    }

    // Выводим результат
    cout << "Count = "<<  firstWordCount  << endl;
    for (int number : resultNumbers) {
        cout << number << endl;
    }

    return 0;
}


