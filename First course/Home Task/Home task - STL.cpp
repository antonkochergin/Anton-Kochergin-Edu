#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// текущее состояния слова
void printWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// вывод алфавита
void printAlphabet(const vector<bool>& alphabet) {
    for (char c = 'a'; c <= 'z'; ++c) {
        if (alphabet[c - 'a']) { 
            cout << c << " ";
        }
        else {
            cout << "- ";
        }
    }
    cout << endl;
}

// виселица
void drawHangman(int attempts) {
    cout << "  ____" << endl;
    cout << " |    |" << endl;
    cout << " |    " << (attempts > 0 ? "O" : "") << endl;
    cout << " |   " << (attempts > 1 ? "/" : " ") << (attempts > 2 ? "|" : "") << (attempts > 3 ? "\\" : "") << endl; //если усл., то ... , иначе ...
    cout << " |   " << (attempts > 4 ? "/" : " ") << " " << (attempts > 5 ? "\\" : "") << endl;
    cout << "_|_" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // генератор рандомных чисел 
    setlocale(LC_ALL, "RUS");
    vector<string> words = {
        "cat" , "food" , "good" , "managament" , "computer"
    };

    // выбор случайного слова
    string word = words[rand() % words.size()];
    vector<bool> guessed(word.length(), false); // отслеживание угаданных букв
    vector<bool> alphabet(26, true); //  отслеживание доступных букв алфавита
    int flag = 1;
    int attempts = 0; // кол-во попыток
    const int maxAttempts = 6; // ограничение попыток
    bool wordGuessed = false; // угадано слово или нет 

    cout << "Добро пожаловать в игру 'Виселица'!" << endl;

    while (attempts < maxAttempts && !wordGuessed && flag != 0) {
        cout << "\nТекущее состояние слова: ";
        printWord(word, guessed); // текущее состояние слова 

        
        cout << "Оставшиеся буквы: ";
        printAlphabet(alphabet); // доступные буквы 

        cout << "Введите букву или слово целиком: ";
        string input;
        cin >> input; // Ввод буквы или слова 

        // регистр 
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input.length() == 1) { // одна буква
            char letter = input[0];
            if (alphabet[letter - 'a']) { // не использовалась
                alphabet[letter - 'a'] = false; // отмечаем что использовали
                bool found = false; // найдена буква или нет
                for (size_t i = 0; i < word.length(); ++i) {
                    if (word[i] == letter) {
                        guessed[i] = true; // отмечаем что угадана
                        found = true;
                    }
                }
                if (!found) { // если нету в слове 
                    ++attempts; // увеличиваем счётчик
                    cout << "Буквы '" << letter << "' нет в слове. Осталось попыток: " << maxAttempts - attempts << endl;
                }
            }
            else {
                cout << "Вы уже вводили эту букву." << endl; // сообщение о повторном вводе буквы
            }
        }
        else { // слово целиком
            if (input == word) { // слово угадано
                wordGuessed = true; 
                cout << "\nПоздравляем! Вы угадали слово: " << word << endl;
                flag = 0;
            }
            else {
                attempts = 6; // увеличиваем счётчик 
            }
        }

        // проверка на то, угадано слово по буквам или нет 
        wordGuessed = all_of(guessed.begin(), guessed.end(), [](bool b) { return b; });

        //  виселица
        drawHangman(attempts);
    }
    if (flag == 1) {
        if (wordGuessed) {
            cout << "\nПоздравляем! Вы угадали слово: " << word << endl;
        }
        else {
            cout << "\nВы проиграли. Загаданное слово было: " << word << endl;
        }
    }
    return 0;
}