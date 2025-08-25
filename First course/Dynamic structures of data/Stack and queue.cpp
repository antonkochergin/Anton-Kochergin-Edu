// Структура для элемента стека (LIFO - Last In First Out)
struct stack {
    int inf;       // Значение элемента
    stack* next;   // Указатель на следующий элемент
};

// Структура для элемента очереди (FIFO - First In First Out)
struct queue {
    int inf;       // Значение элемента
    queue* next;   // Указатель на следующий элемент
};

// Добавление элемента в стек
void stack_push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;  // Новый элемент становится вершиной стека
    h = r;
}

// Извлечение элемента из стека
int stack_pop(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;  // Перемещаем указатель на следующий элемент
    delete r;     // Освобождаем память
    return i;     // Возвращаем значение извлеченного элемента
}

// Добавление элемента в очередь
void queue_push(queue*& h, queue*& t, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = nullptr;
    if (!h) {
        h = t = r;  // Если очередь пуста, новый элемент становится и головой и хвостом
    }
    else {
        t->next = r; // Иначе добавляем в конец
        t = r;
    }
}

// Извлечение элемента из очереди
int queue_pop(queue*& h, queue*& t) {
    int i = h->inf;
    queue* r = h;
    h = h->next;    // Перемещаем указатель на следующий элемент
    if (!h) {
        t = nullptr;   // Если очередь стала пустой, обнуляем хвост
    }
    delete r;       // Освобождаем память
    return i;       // Возвращаем значение извлеченного элемента
}

// Разворот стека (используется в задачах 3 и 4)
void reverse(stack*& h) {
    stack* head1 = nullptr;
    while (h) {
        stack_push(head1, stack_pop(h));  // Переносим элементы в новый стек
    }
    h = head1;  // Теперь стек развернут
}

// Проверка числа на простоту
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}


//Задача 1 Создать очередь из целых чисел. Выполнить циклический сдвиг очереди так,
// чтобы на первом месте было первое простое число
queue* shiftQueueToFirstPrime(queue*& h, queue*& t) {
    while (h) {  // Пока очередь не пуста
        int x = h->inf;  // Смотрим первый элемент (не извлекая)
        if (isPrime(x)) {
            return h;  // Если простое — возвращаем текущую очередь
        }
        else {
            // Удаляем из начала и добавляем в конец
            queue_pop(h, t);
            queue_push(h, t, x);
        }
    }
    return h;  // Если простых чисел нет, возвращаем исходную очередь (уже пустую)
}


//Задача 2 Создать очередь, содержащую целые числа. После всех чисел, 
// равных минимальному числу, вставить последний четный элемент.
queue* insertLastEvenAfterMin(queue*& h, queue*& t) {
    if (!h) return nullptr;  // Если очередь пуста

    // Шаг 1: Находим минимальный элемент и последний чётный
    int min_val = h->inf;
    int last_even = -1;
    int queue_size = 0;

    // Первый проход с удалением и вставкой
    while (queue_size == 0 || h->inf != min_val) {
        int x = queue_pop(h, t);
        if (x < min_val) min_val = x;
        if (x % 2 == 0) last_even = x;
        queue_push(h, t, x);
        queue_size++;
    }

    // Шаг 2: Создаем новую очередь с вставками
    queue* res_h = nullptr;
    queue*res_t = nullptr;
    for (int i = 0; i < queue_size; i++) {
        int x = queue_pop(h, t);
        queue_push(res_h, res_t, x);
        if (x == min_val) {
            queue_push(res_h, res_t, last_even);
        }
    }

    return res_h;
}
//Задача 3 Создать стек, содержащий целые числа. Перед  всеми минимальными числами вставить максимальное число. 
// Порядок следования в результате должен совпадать с порядком следования ввода.
stack* insertMaxBeforeMinInStack(stack* h) {
    if (!h) return nullptr;

    // Находим min и max
    stack* temp = nullptr;
    int min_val = h->inf, max_val = h->inf;

    // Первый проход
    while (h) {
        int x = stack_pop(h);
        if (x < min_val) min_val = x;
        if (x > max_val) max_val = x;
        stack_push(temp, x);
    }

    // Восстанавливаем стек и строим результат
    stack* res = nullptr;
    while (temp) {
        int x = stack_pop(temp);
        stack_push(h, x);
        if (x == min_val) {
            stack_push(res, max_val);
        }
        stack_push(res, x);
    }

    // Разворачиваем результат
    stack* final_res = nullptr;
    while (res) {
        stack_push(final_res, stack_pop(res));
    }

    return final_res;
}

//Задача 4 Создать стек, содержащий целые числа от 0 до 20. В новый стек вывести сначала однозначные, потом двузначные числа. 
// Порядок следования чисел в новом стеке должен совпадать с первоначальным.
stack* rearrangeStackSingleDoubleDigit(stack* h) {
    stack* single_digit = nullptr;  // Для чисел 0-9
    stack* double_digit = nullptr;  // Для чисел 10-20

    // Разделяем числа на два стека
    while (h) {
        int x = stack_pop(h);
        if (x >= 0 && x <= 9) {
            stack_push(single_digit, x);
        }
        else {
            stack_push(double_digit, x);
        }
    }

    // Создаем результирующий стек
    stack* res = nullptr;

    // Сначала переносим двузначные числа (в обратном порядке)
    while (double_digit) {
        stack_push(res, stack_pop(double_digit));
    }

    // Затем переносим однозначные числа (в обратном порядке)
    while (single_digit) {
        stack_push(res, stack_pop(single_digit));
    }

    return res;
}