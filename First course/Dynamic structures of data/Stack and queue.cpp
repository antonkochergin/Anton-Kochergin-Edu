// ��������� ��� �������� ����� (LIFO - Last In First Out)
struct stack {
    int inf;       // �������� ��������
    stack* next;   // ��������� �� ��������� �������
};

// ��������� ��� �������� ������� (FIFO - First In First Out)
struct queue {
    int inf;       // �������� ��������
    queue* next;   // ��������� �� ��������� �������
};

// ���������� �������� � ����
void stack_push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;  // ����� ������� ���������� �������� �����
    h = r;
}

// ���������� �������� �� �����
int stack_pop(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;  // ���������� ��������� �� ��������� �������
    delete r;     // ����������� ������
    return i;     // ���������� �������� ������������ ��������
}

// ���������� �������� � �������
void queue_push(queue*& h, queue*& t, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = nullptr;
    if (!h) {
        h = t = r;  // ���� ������� �����, ����� ������� ���������� � ������� � �������
    }
    else {
        t->next = r; // ����� ��������� � �����
        t = r;
    }
}

// ���������� �������� �� �������
int queue_pop(queue*& h, queue*& t) {
    int i = h->inf;
    queue* r = h;
    h = h->next;    // ���������� ��������� �� ��������� �������
    if (!h) {
        t = nullptr;   // ���� ������� ����� ������, �������� �����
    }
    delete r;       // ����������� ������
    return i;       // ���������� �������� ������������ ��������
}

// �������� ����� (������������ � ������� 3 � 4)
void reverse(stack*& h) {
    stack* head1 = nullptr;
    while (h) {
        stack_push(head1, stack_pop(h));  // ��������� �������� � ����� ����
    }
    h = head1;  // ������ ���� ���������
}

// �������� ����� �� ��������
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}


//������ 1 ������� ������� �� ����� �����. ��������� ����������� ����� ������� ���,
// ����� �� ������ ����� ���� ������ ������� �����
queue* shiftQueueToFirstPrime(queue*& h, queue*& t) {
    while (h) {  // ���� ������� �� �����
        int x = h->inf;  // ������� ������ ������� (�� ��������)
        if (isPrime(x)) {
            return h;  // ���� ������� � ���������� ������� �������
        }
        else {
            // ������� �� ������ � ��������� � �����
            queue_pop(h, t);
            queue_push(h, t, x);
        }
    }
    return h;  // ���� ������� ����� ���, ���������� �������� ������� (��� ������)
}


//������ 2 ������� �������, ���������� ����� �����. ����� ���� �����, 
// ������ ������������ �����, �������� ��������� ������ �������.
queue* insertLastEvenAfterMin(queue*& h, queue*& t) {
    if (!h) return nullptr;  // ���� ������� �����

    // ��� 1: ������� ����������� ������� � ��������� ������
    int min_val = h->inf;
    int last_even = -1;
    int queue_size = 0;

    // ������ ������ � ��������� � ��������
    while (queue_size == 0 || h->inf != min_val) {
        int x = queue_pop(h, t);
        if (x < min_val) min_val = x;
        if (x % 2 == 0) last_even = x;
        queue_push(h, t, x);
        queue_size++;
    }

    // ��� 2: ������� ����� ������� � ���������
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
//������ 3 ������� ����, ���������� ����� �����. �����  ����� ������������ ������� �������� ������������ �����. 
// ������� ���������� � ���������� ������ ��������� � �������� ���������� �����.
stack* insertMaxBeforeMinInStack(stack* h) {
    if (!h) return nullptr;

    // ������� min � max
    stack* temp = nullptr;
    int min_val = h->inf, max_val = h->inf;

    // ������ ������
    while (h) {
        int x = stack_pop(h);
        if (x < min_val) min_val = x;
        if (x > max_val) max_val = x;
        stack_push(temp, x);
    }

    // ��������������� ���� � ������ ���������
    stack* res = nullptr;
    while (temp) {
        int x = stack_pop(temp);
        stack_push(h, x);
        if (x == min_val) {
            stack_push(res, max_val);
        }
        stack_push(res, x);
    }

    // ������������� ���������
    stack* final_res = nullptr;
    while (res) {
        stack_push(final_res, stack_pop(res));
    }

    return final_res;
}

//������ 4 ������� ����, ���������� ����� ����� �� 0 �� 20. � ����� ���� ������� ������� �����������, ����� ���������� �����. 
// ������� ���������� ����� � ����� ����� ������ ��������� � ��������������.
stack* rearrangeStackSingleDoubleDigit(stack* h) {
    stack* single_digit = nullptr;  // ��� ����� 0-9
    stack* double_digit = nullptr;  // ��� ����� 10-20

    // ��������� ����� �� ��� �����
    while (h) {
        int x = stack_pop(h);
        if (x >= 0 && x <= 9) {
            stack_push(single_digit, x);
        }
        else {
            stack_push(double_digit, x);
        }
    }

    // ������� �������������� ����
    stack* res = nullptr;

    // ������� ��������� ���������� ����� (� �������� �������)
    while (double_digit) {
        stack_push(res, stack_pop(double_digit));
    }

    // ����� ��������� ����������� ����� (� �������� �������)
    while (single_digit) {
        stack_push(res, stack_pop(single_digit));
    }

    return res;
}