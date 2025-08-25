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
        //��������� ����� 
        while (n > 0) {
            int digit = n % 10; 
            Digits.insert(digit);
            n /= 10; 
        }

        //���� ����� ����������, �� �������� ��� ������������ 
        if (num >= 100 && num <= 999) {
            n = num; 
            //��������� �����
            while (n > 0) {
                int digit = n % 10; 
                ThreeDigits.insert(digit); 
                n /= 10;
            }
        }
    }

    //���������
    set<int> result;
    //��������� �� ����������
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
    //����
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Err" << endl;
        return 1;
    }

    //������ ������ � ���� ������ 
    string line;
    getline(inputFile, line);
    inputFile.close();

    // ��������� ����� ��� ��������� ������ �� ��������
    stringstream ss(line);
    string el;
    vector<string> els; // ������ ��� �������� ���������
    //(item , count)
    map<int, int> numberCounts; // ������� ��� �������� ���������� ��������� 
    string firstWord; // ������ �����
    bool isFirstWord = true; // ���� ��� ����������� ������� �����



    // ��������� ������ �� ��������
    while (ss >> el) {
        els.push_back(el);

        // ���� ������� - �����, ��������� ��� � �������
        try {
            int number = stoi(el); // �������� ������������� ������� � �����
            numberCounts[number]++; // ����������� ������� ��� ����� �����
        }
        catch (invalid_argument&) {
            // ���� ������� �� ����� , �� ��� - �����
            if (isFirstWord) {
                firstWord = el; // ���������� ������ �����
                isFirstWord = false;
            }
        }
    }



    // ������� ��� ����������� ������ ����� - ������ �� ���� 
    int firstWordCount = 0;
    for (const string& t : els) {
        if (t == firstWord) {
            firstWordCount++;
        }
    }

    // ������� ��� �����, ������� ����������� ������� �� ���, ������� ������ ����� - ������ �� ������ 
    set<int> resultNumbers; //���������
    for (const auto& pair : numberCounts) {
        if (pair.second == firstWordCount) {
            resultNumbers.insert(pair.first); 
        }
    }

    // ������� ���������
    cout << "Count = "<<  firstWordCount  << endl;
    for (int number : resultNumbers) {
        cout << number << endl;
    }

    return 0;
}


