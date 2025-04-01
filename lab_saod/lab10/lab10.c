#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;
int swaps = 0;

// Функция для обмена элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swaps += 3; // Учитываем 3 операции пересылки
}

// Просеивание вниз (sift down)
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    comparisons++;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    comparisons++;
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Построение пирамиды
void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Пирамидальная сортировка
void heapSort(int arr[], int n) {
    buildHeap(arr, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Генерация массива
void generateArray(int arr[], int n, int type) {
    switch (type) {
        case 0: // Убывающий
            for (int i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 1: // Случайный
            for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
            break;
        case 2: // Возрастающий
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            break;
    }
}

// Подсчет контрольной суммы
int controlSum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}

// Подсчет числа серий
int countSeries(int arr[], int n) {
    int series = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) series++;
    }
    return series;
}

// Вывод таблицы для построения пирамиды
void printHeapBuildTable() {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("Трудоемкость построения пирамиды\n");
    printf("+------+----------------+-------------------+-------------------+-------------------+\n");
    printf("|  N   | M+C теоретич.  | Mф+Сф (убыв.)     | Mф+Сф (случ.)     | Mф+Сф (возр.)     |\n");
    printf("+------+----------------+-------------------+-------------------+-------------------+\n");

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int total_ops[3] = {0};

        for (int type = 0; type < 3; type++) {
            int arr[n];
            generateArray(arr, n, type);
            
            comparisons = 0;
            swaps = 0;
            buildHeap(arr, n);
            
            total_ops[type] = comparisons + swaps;
        }

        printf("| %4d | %14d | %17d | %17d | %17d |\n", 
               n, 2 * n, total_ops[0], total_ops[1], total_ops[2]);
    }
    printf("+------+----------------+-------------------+-------------------+-------------------+\n");
}

// Вывод таблицы для сортировки
void printHeapSortTable() {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("Трудоемкость пирамидальной сортировки\n");
    printf("+------+------------------+-------------------+------------------+\n");
    printf("|  N   | Убывающий массив | Возрастающий массив | Случайный массив |\n");
    printf("+------+------------------+-------------------+------------------+\n");

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int total_ops[3] = {0};

        for (int type = 0; type < 3; type++) {
            int arr[n];
            generateArray(arr, n, type);
            
            comparisons = 0;
            swaps = 0;
            heapSort(arr, n);
            
            total_ops[type] = comparisons + swaps;
        }

        printf("| %4d | %16d | %17d | %16d |\n", 
               n, total_ops[0], total_ops[2], total_ops[1]);
    }
    printf("+------+------------------+-------------------+------------------+\n");
    
}

int main() {
    srand(time(NULL));
    
    printf("Исследование трудоемкости построения пирамиды:\n");
    printHeapBuildTable();
    
    printf("\nИсследование трудоемкости пирамидальной сортировки:\n");
    printHeapSortTable();
    
    return 0;
}