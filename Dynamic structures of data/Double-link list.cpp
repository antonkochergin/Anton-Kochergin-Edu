#include <iostream>
using namespace std;

struct list {
    int inf;
    list* next;
    list* prev;
};

// Вставка элемента в конец списка
void push(list*& h, list*& t, int x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// Печать списка
void print(list* h) {
    list* p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

// Удаление элемента из списка
void del_node(list*& h, list*& t, list* r) {
    if (!r) return;

    if (r == h && r == t) {
        h = t = NULL;
    }
    else if (r == h) {
        h = h->next;
        h->prev = NULL;
    }
    else if (r == t) {
        t = t->prev;
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

///1 задание Создать двусвязный список, содержащий целые числа. Удалить первый и последний нечетный элемент
// Функция для удаления первого и последнего нечетных элементов
void removeFirstLastOdd(list*& h, list*& t) {
    if (!h) return;

    list* firstOdd = NULL;
    list* lastOdd = NULL;
    list* current = h;

    // Находим первый и последний нечетные элементы
    while (current) {
        if (current->inf % 2 != 0) {
            if (!firstOdd) {
                firstOdd = current;  // Первый нечетный
            }
            lastOdd = current;      // Последний нечетный (будет перезаписываться)
        }
        current = current->next;
    }

    // Удаляем элементы, если они найдены
    if (firstOdd) {
        del_node(h, t, firstOdd);
    }
    if (lastOdd && lastOdd != firstOdd) {  // Проверяем, чтобы не удалить один элемент дважды
        del_node(h, t, lastOdd);
    }
}


///2 задача Создать двусвязный список из целых чисел. Выполнить циклический сдвиг списка так, чтобы на первом месте было первое простое число
// Циклический сдвиг до первого простого числа
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

void shiftToFirstPrime(list*& h, list*& t) {
    if (!h) return;

    list* current = h;
    while (current) {
        if (isPrime(current->inf)) {
            // Если простое число уже первое - ничего не делаем
            if (current == h) return;

            // Разрываем связи перед простым числом
            current->prev->next = NULL;
            t->next = h;
            h->prev = t;

            // Обновляем голову и хвост
            t = current->prev;
            h = current;
            h->prev = NULL;

            return;
        }
        current = current->next;
    }
}

///3 задача Используя кольцевой список, решить задачу Иосифа: Дан список из 𝑁 чисел. Удалять каждый 𝐾-ый элемент до тех пор, 
//пока не останется единственный элемент. Вывести его на экран.
int josephusProblem(list*& h, int k) {
    if (!h) return -1;  // Если список пуст

    list* current = h;
    while (current->next != current) {  // Пока не останется один элемент
        // Находим k-ый элемент
        for (int i = 1; i < k; ++i) {
            current = current->next;
        }

        // Удаляем k-ый элемент
        list* toDelete = current;
        current->prev->next = current->next; //Буквально перепрыгиваем через 1 и удаляем 

        current->next->prev = current->prev;
        current = current->next;

        // Обновляем голову, если удаляем ее
        if (toDelete == h) {
            h = current;
        }

        delete toDelete;
    }

    int result = current->inf;
    delete current;
    h = nullptr;
    return result;
}

//int main() {
//    list* head = nullptr;
//    list* tail = nullptr;
//
//    int n, k;
//    cout << "Введите N (количество людей): ";
//    cin >> n;
//    cout << "Введите K (шаг удаления): ";
//    cin >> k;
//
//    // Создаем кольцевой список
//    for (int i = 1; i <= n; ++i) {
//        push(head, tail, i);
//    }
//
//    // Решаем задачу Иосифа
//    int survivor = josephusProblem(head, k);
//    cout << "Выживший: " << survivor << endl;
//
//    return 0;
//}
//
//
