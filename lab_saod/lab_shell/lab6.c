#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // Для генерации случайных чисел

void computeKnuthSteps(int n, int *steps, int *stepCount) {
    int gap = 1;
    *stepCount = 0;

    while (gap < n) {
        steps[(*stepCount)++] = gap;
        gap = 3 * gap + 1;
    }
}

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

void shellSort(int *A, int n, int *M, int *C) {
    int steps[100];
    int stepCount;
    computeKnuthSteps(n, steps, &stepCount);

    *M = 0;
    *C = 0;

    for (int k = stepCount - 1; k >= 0; k--) {
        int gap = steps[k];

        // Сортировка вставками с шагом gap
        for (int i = gap; i < n; i++) {
            (*M)++;
            int t = A[i];
            int j = i - gap;

            while (j >= 0 && ((*C)++, t < A[j])) {
                (*M)++;
                A[j + gap] = A[j];
                j = j - gap;
            }

            (*M)++;
            A[j + gap] = t;
        }
    }
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("| n    | Шаги по Кнуту (h₁ ... hₙ) | Insert M + C | Shell M + C         |\n");
    printf("|------|--------------------------|------------|-----------------------|\n");

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        int *arr_copy = (int *)malloc(n * sizeof(int));

        // Заполняем массив случайными значениями
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000; // Случайные числа от 0 до 999
            arr_copy[j] = arr[j];
        }

        int M_insert, C_insert;
        int M_shell, C_shell;

        // Выполняем сортировку вставками
        insertSort(arr_copy, n, &M_insert, &C_insert);

        // Выполняем сортировку Шелла
        shellSort(arr, n, &M_shell, &C_shell);

        // Вывод результатов
        printf("| %4d | ", n);

        // Вывод шагов по формуле Кнута
        int steps[100];
        int stepCount;
        computeKnuthSteps(n, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
        // Добавляем пробелы для выравнивания
        for (int j = stepCount; j < 7; j++) {
            printf("   ");
        }

        // Вывод фактических значений M + C для Insert Sort и Shell Sort
        printf("      | %8d   | %12d           |\n", M_insert + C_insert, M_shell + C_shell);

        free(arr);
        free(arr_copy);
    }

    return 0;
}