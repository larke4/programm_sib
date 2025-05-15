#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Структура узла списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура стека
typedef struct {
    Node* top;
} Stack;

// Структура очереди
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Инициализация стека
void initStack(Stack* s) {
    s->top = NULL;
}

// Добавление элемента в стек
void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Заполнение стека возрастающими числами
void fillStackAscending(Stack* s, int n) {
    for (int i = 1; i <= n; i++) {
        push(s, i);
    }
}

// Заполнение стека убывающими числами
void fillStackDescending(Stack* s, int n) {
    for (int i = n; i >= 1; i--) {
        push(s, i);
    }
}

// Заполнение стека случайными числами
void fillStackRandom(Stack* s, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        push(s, val);
    }
}

// Инициализация очереди
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Добавление элемента в очередь
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Заполнение очереди возрастающими числами
void fillQueueAscending(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

// Заполнение очереди убывающими числами
void fillQueueDescending(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}

// Заполнение очереди случайными числами
void fillQueueRandom(Queue* q, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, val);
    }
}

// Печать списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Вычисление контрольной суммы
int calculateChecksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Подсчет серий (неубывающих последовательностей)
int countSeries(Node* head) {
    if (head == NULL) return 0;
    
    int count = 1;
    Node* current = head;
    
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

// Анализ упорядоченности последовательности
void analyzeOrder(Node* head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    int total = 1;
    int series = 1;
    int max_len = 1;
    int current_len = 1;
    Node* current = head;
    
    while (current->next != NULL) {
        total++;
        if (current->data <= current->next->data) {
            current_len++;
            if (current_len > max_len) max_len = current_len;
        } else {
            series++;
            current_len = 1;
        }
        current = current->next;
    }
    
    printf("    Анализ упорядоченности:\n");
    printf("    • Всего элементов: %d\n", total);
    printf("    • Количество серий: %d\n", series);
    printf("    • Длина самой длинной серии: %d\n", max_len);
    printf("    • Средняя длина серии: %.2f\n", (float)total/series);
    printf("    • Степень упорядоченности: %.2f%%\n", 
           (1 - (float)(series-1)/(total-1)) * 100);
}

// Проверка на неубывающую последовательность
bool isNonDecreasing(Node* head) {
    while (head->next != NULL) {
        if (head->data > head->next->data) return false;
        head = head->next;
    }
    return true;
}

// Очистка стека
void clearStack(Stack* s) {
    Node* current = s->top;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    s->top = NULL;
}

// Очистка очереди
void clearQueue(Queue* q) {
    Node* current = q->front;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    q->front = q->rear = NULL;
}

// Демонстрационная функция
void demo() {
    Stack s;
    Queue q;
    int checksum, series;
    
    printf("=== Демонстрация работы со стеком и очередью ===\n\n");
    
    // Тестирование стека
    printf("1. Тестирование стека:\n");
    initStack(&s);
    
    // Возрастающие числа
    fillStackAscending(&s, 10);
    printf("  - Возрастающие числа (1-10): ");
    printList(s.top);
    checksum = calculateChecksum(s.top);
    series = countSeries(s.top);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(s.top) ? "Да" : "Нет");
    analyzeOrder(s.top);
    clearStack(&s);
    
    // Убывающие числа
    fillStackDescending(&s, 10);
    printf("\n  - Убывающие числа (10-1): ");
    printList(s.top);
    checksum = calculateChecksum(s.top);
    series = countSeries(s.top);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(s.top) ? "Да" : "Нет");
    analyzeOrder(s.top);
    clearStack(&s);
    
    // Случайные числа
    fillStackRandom(&s, 10, 10, 20);
    printf("\n  - Случайные числа (10-20): ");
    printList(s.top);
    checksum = calculateChecksum(s.top);
    series = countSeries(s.top);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(s.top) ? "Да" : "Нет");
    analyzeOrder(s.top);
    clearStack(&s);
    
    // Тестирование очереди
    printf("\n2. Тестирование очереди:\n");
    initQueue(&q);
    
    // Возрастающие числа
    fillQueueAscending(&q, 10);
    printf("  - Возрастающие числа (1-10): ");
    printList(q.front);
    checksum = calculateChecksum(q.front);
    series = countSeries(q.front);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(q.front) ? "Да" : "Нет");
    analyzeOrder(q.front);
    clearQueue(&q);
    
    // Убывающие числа
    fillQueueDescending(&q, 10);
    printf("\n  - Убывающие числа (10-1): ");
    printList(q.front);
    checksum = calculateChecksum(q.front);
    series = countSeries(q.front);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(q.front) ? "Да" : "Нет");
    analyzeOrder(q.front);
    clearQueue(&q);
    
    // Случайные числа
    fillQueueRandom(&q, 10, 10, 20);
    printf("\n  - Случайные числа (10-20): ");
    printList(q.front);
    checksum = calculateChecksum(q.front);
    series = countSeries(q.front);
    printf("    Контрольная сумма: %d\n", checksum);
    printf("    Количество серий: %d\n", series);
    printf("    Проверка упорядоченности: %s\n", isNonDecreasing(q.front) ? "Да" : "Нет");
    analyzeOrder(q.front);
    clearQueue(&q);

    printf("\n=== Демонстрация завершена ===\n");
}

int main() {
    demo();
    return 0;
}