#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSort(int *A, int n, int *M, int *C) {
    (*M) = 0;
    (*C) = 0;
    for (int i = 1; i < n; i++) {
        (*M)++;
        int t = A[i];
        int j = i - 1;
        while (j >= 0 && ((*C)++, t < A[j])) {
            (*M)++;
            A[j + 1] = A[j];
            j = j - 1;
        }
        (*M)++;
        A[j + 1] = t;
    }
}

void generateArray(int arr[], int n, char type) {
    if (type == 'a') { // возрастающий массив
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    } else if (type == 'd') { // убывающий массив
        for (int i = 0; i < n; i++) {
            arr[i] = n - i - 1;
        }
    } else if (type == 'r') { // случайный массив
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }
    }
}

void calculateTheoretical(int n, int *M_cp, int *C_cp, int *M_min, int *C_min, int *M_max, int *C_max) {
    *M_cp = (n * n - n) / 4 + n - 1;
    *C_cp = (n * n - n) / 4;

    *M_min = 2 * (n - 1);
    *C_min = n - 1;

    *M_max = (n * n - n) / 2 + 2 * n - 2;
    *C_max = (n * n - n) / 2;
}

// Функции второго кода
void selectSort_good(int arr[], int n, int *swaps, int *comparisons) {
    *swaps = 0;
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            (*swaps)++;
        }
    }
}

void bubbleSort(int arr[], int n, int *M, int *C) {
    int i, j, temp;
    *M = 0;
    *C = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*C)++;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*M)++;
            }
        }
    }
}

void shaker_sort(int arr[], int size, int *comp, int *swap) {
    int left = 0, right = size - 1, last = right;
    *comp = *swap = 0;

    while (left < right) {
        for (int j = right; j > left; j--) {
            (*comp)++;
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                *swap += 3;
                last = j;
            }
        }
        left = last;

        for (int j = left; j < right; j++) {
            (*comp)++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                *swap += 3;
                last = j;
            }
        }
        right = last;
    }
}

void calculateTheoretical2(int n, int *M_select, int *C_select, int *M_bubble, int *C_bubble, int *M_shaker, int *C_shaker, int *M_insert, int *C_insert) {
    *M_select = 3 * (n - 1);
    *C_select = (n * n - n) / 2;

    *M_bubble = 3 * ((n * n - n) / 4);
    *C_bubble = (n * n - n) / 2;

    *M_shaker = 3 * (((n * n - n) / 2) - ((n * n - n) / 4));
    *C_shaker = (n * n - n) / 2;

    *M_insert = (n * n - n) / 4 + n - 1;
    *C_insert = (n * n - n) / 4;
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));

    // Первый код
    printf("Трудоемкость метода прямого включения InsertSort\n");
    printf("--------------------------------------------------\n");
    printf("|  N  | M+C теоретич. |   Mфакт + Cфакт          |\n");
    printf("--------------------------------------------------\n");
    printf("|     |               | Убыв.  | Случ.  | Возр.  |\n");
    printf("--------------------------------------------------\n");

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int arr[n];

// Теоретическая оценка
        int M_cp, C_cp, M_min, C_min, M_max, C_max;
        calculateTheoretical(n, &M_cp, &C_cp, &M_min, &C_min, &M_max, &C_max);

        // Фактические замеры
        int ascComp, ascMoves, descComp, descMoves, randComp, randMoves;

        // Возрастающий массив
        generateArray(arr, n, 'a');
        int arrCopy[n];
        for (int j = 0; j < n; j++) arrCopy[j] = arr[j];
        insertSort(arrCopy, n, &ascMoves, &ascComp);

        // Убывающий массив
        generateArray(arr, n, 'd');
        for (int j = 0; j < n; j++) arrCopy[j] = arr[j];
        insertSort(arrCopy, n, &descMoves, &descComp);

        // Случайный массив
        generateArray(arr, n, 'r');
        for (int j = 0; j < n; j++) arrCopy[j] = arr[j];
        insertSort(arrCopy, n, &randMoves, &randComp);

        printf("| %-3d | %-13d | %-6d | %-6d | %-6d |\n",
               n, M_max + C_max, descMoves + descComp, randMoves + randComp, ascMoves + ascComp);
    }

    printf("--------------------------------------------------\n");

    // Второй код
    printf("\nТрудоёмкость квадратичных методов сортировки\n");
    printf("-------------------------------------------\n");
    printf("| n  | Select | Bubble | Shaker | Insert |\n");
    printf("-------------------------------------------\n");

    for (int k = 0; k < numSizes; k++) { // Используем другую переменную для цикла
        int n = sizes[k];
        int M_select, C_select, M_bubble, C_bubble, M_shaker, C_shaker, M_insert, C_insert;

        calculateTheoretical2(n, &M_select, &C_select, &M_bubble, &C_bubble, &M_shaker, &C_shaker, &M_insert, &C_insert);

        printf("| %-3d | %-6d | %-6d | %-6d | %-6d |\n",
               n,
               M_select + C_select,
               M_bubble + C_bubble,
               M_shaker + C_shaker,
               M_insert + C_insert);
        printf("-------------------------------------------\n");
    }

    return 0;
}