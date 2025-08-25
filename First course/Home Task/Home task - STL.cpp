#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// ������� ��������� �����
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

// ����� ��������
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

// ��������
void drawHangman(int attempts) {
    cout << "  ____" << endl;
    cout << " |    |" << endl;
    cout << " |    " << (attempts > 0 ? "O" : "") << endl;
    cout << " |   " << (attempts > 1 ? "/" : " ") << (attempts > 2 ? "|" : "") << (attempts > 3 ? "\\" : "") << endl; //���� ���., �� ... , ����� ...
    cout << " |   " << (attempts > 4 ? "/" : " ") << " " << (attempts > 5 ? "\\" : "") << endl;
    cout << "_|_" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // ��������� ��������� ����� 
    setlocale(LC_ALL, "RUS");
    vector<string> words = {
        "cat" , "food" , "good" , "managament" , "computer"
    };

    // ����� ���������� �����
    string word = words[rand() % words.size()];
    vector<bool> guessed(word.length(), false); // ������������ ��������� ����
    vector<bool> alphabet(26, true); //  ������������ ��������� ���� ��������
    int flag = 1;
    int attempts = 0; // ���-�� �������
    const int maxAttempts = 6; // ����������� �������
    bool wordGuessed = false; // ������� ����� ��� ��� 

    cout << "����� ���������� � ���� '��������'!" << endl;

    while (attempts < maxAttempts && !wordGuessed && flag != 0) {
        cout << "\n������� ��������� �����: ";
        printWord(word, guessed); // ������� ��������� ����� 

        
        cout << "���������� �����: ";
        printAlphabet(alphabet); // ��������� ����� 

        cout << "������� ����� ��� ����� �������: ";
        string input;
        cin >> input; // ���� ����� ��� ����� 

        // ������� 
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input.length() == 1) { // ���� �����
            char letter = input[0];
            if (alphabet[letter - 'a']) { // �� ��������������
                alphabet[letter - 'a'] = false; // �������� ��� ������������
                bool found = false; // ������� ����� ��� ���
                for (size_t i = 0; i < word.length(); ++i) {
                    if (word[i] == letter) {
                        guessed[i] = true; // �������� ��� �������
                        found = true;
                    }
                }
                if (!found) { // ���� ���� � ����� 
                    ++attempts; // ����������� �������
                    cout << "����� '" << letter << "' ��� � �����. �������� �������: " << maxAttempts - attempts << endl;
                }
            }
            else {
                cout << "�� ��� ������� ��� �����." << endl; // ��������� � ��������� ����� �����
            }
        }
        else { // ����� �������
            if (input == word) { // ����� �������
                wordGuessed = true; 
                cout << "\n�����������! �� ������� �����: " << word << endl;
                flag = 0;
            }
            else {
                attempts = 6; // ����������� ������� 
            }
        }

        // �������� �� ��, ������� ����� �� ������ ��� ��� 
        wordGuessed = all_of(guessed.begin(), guessed.end(), [](bool b) { return b; });

        //  ��������
        drawHangman(attempts);
    }
    if (flag == 1) {
        if (wordGuessed) {
            cout << "\n�����������! �� ������� �����: " << word << endl;
        }
        else {
            cout << "\n�� ���������. ���������� ����� ����: " << word << endl;
        }
    }
    return 0;
}