#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для сортировки методом Шелла с заданной последовательностью шагов
void shellSort(int arr[], int n, int *comparisons, int *moves, int gaps[], int gaps_count) {
    int gap, i, j;
    int temp;

    *comparisons = 0;
    *moves = 0;

    for (int k = 0; k < gaps_count; k++) {
        gap = gaps[k];
        for (i = gap; i < n; i++) {
            temp = arr[i];
            (*moves)++;
            for (j = i; j >= gap; j -= gap) {
                (*comparisons)++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    (*moves)++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            (*moves)++;
        }
    }
}

// Функция для сортировки методом прямого включения (InsertSort)
void insertSort(int arr[], int n, int *comparisons, int *moves) {
    int i, j, key;
    *comparisons = 0;
    *moves = 0;

    for (i = 1; i < n; i++) {
        key = arr[i];
        (*moves)++;
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            (*moves)++;
            j--;
        }
        (*comparisons)++; // Учет последнего сравнения
        arr[j + 1] = key;
        (*moves)++;
    }
}

// Функция для генерации случайного массива
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Функция для вывода таблицы сравнения ShellSort и InsertSort
void printTable1(int n_values[], int size) {
    printf("Таблица 1: Трудоемкость метода Шелла и InsertSort\n");
    printf("| n    | h₁ … hₙ по формуле Д.Кнута | Insert Mф+Cф | Shell Mф+Cф |\n");
    printf("|------|----------------------------|--------------|-------------|\n");

    for (int i = 0; i < size; i++) {
        int n = n_values[i];
        int arr[n], arr_copy[n];
        generateRandomArray(arr, n);

        // Копируем массив для сортировки InsertSort
        for (int j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }

        int comparisons_shell = 0, moves_shell = 0;
        int comparisons_insert = 0, moves_insert = 0;

        // Последовательность шагов по формуле Д. Кнута
        int gaps_knuth[20], knuth_count = 0;
        for (int gap = 1; gap <= n / 3; gap = gap * 3 + 1) {
            gaps_knuth[knuth_count++] = gap;
        }

        // Сортировка ShellSort
        shellSort(arr, n, &comparisons_shell, &moves_shell, gaps_knuth, knuth_count);

        // Сортировка InsertSort
        insertSort(arr_copy, n, &comparisons_insert, &moves_insert);

        // Выводим строку таблицы
        printf("| %-4d | ", n);
        for (int j = knuth_count - 1; j >= 0; j--) {
            printf("%d ", gaps_knuth[j]);
        }
        printf(" | %-12d | %-11d |\n", comparisons_insert + moves_insert, comparisons_shell + moves_shell);
    }
    printf("\n");
}

// Функция для вывода таблицы исследования зависимости от последовательности шагов
void printTable2(int n_values[], int size) {
    printf("Таблица 2: Исследование зависимости трудоемкости ShellSort от последовательности шагов\n");
    printf("| n    | h₁ … hₙ по формуле Д.Кнута | Shell Mф+Сф | h₁ … hₙ по Седжвику | Shell Mф+Сф |\n");
    printf("|------|----------------------------|-------------|---------------------|-------------|\n");

    for (int i = 0; i < size; i++) {
        int n = n_values[i];
        int arr[n], arr_copy[n];
        generateRandomArray(arr, n);

        // Копируем массив для сортировки с другой последовательностью
        for (int j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }

        int comparisons_knuth = 0, moves_knuth = 0;
        int comparisons_sedgewick = 0, moves_sedgewick = 0;

// Последовательность шагов по формуле Д. Кнута
        int gaps_knuth[20], knuth_count = 0;
        for (int gap = 1; gap <= n / 3; gap = gap * 3 + 1) {
            gaps_knuth[knuth_count++] = gap;
        }
        // Сортировка с последовательностью Д. Кнута
        shellSort(arr, n, &comparisons_knuth, &moves_knuth, gaps_knuth, knuth_count);

        // Последовательность шагов по формуле Седжвика
        int gaps_sedgewick[20], sedgewick_count = 0;
        int k = 0;
        while (1) {
            int gap;
            if (k == 0) {
                gap = 1;
            } else {
                gap = 9 * (1 << (2 * k)) - 9 * (1 << k) + 1;
            }
            if (gap > n) break;
            gaps_sedgewick[sedgewick_count++] = gap;
            k++;
        }

        // Сортировка с последовательностью Седжвика
        shellSort(arr_copy, n, &comparisons_sedgewick, &moves_sedgewick, gaps_sedgewick, sedgewick_count);

        // Выводим строку таблицы
        printf("| %-4d | ", n);
        for (int j = knuth_count - 1; j >= 0; j--) {
            printf("%d ", gaps_knuth[j]);
        }
        printf(" | %-11d | ", comparisons_knuth + moves_knuth);
        for (int j = sedgewick_count - 1; j >= 0; j--) {
            printf("%d ", gaps_sedgewick[j]);
        }
        printf(" | %-11d |\n", comparisons_sedgewick + moves_sedgewick);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    // Значения n для исследования
    int n_values[] = {100, 200, 300, 400, 500};
    int size = sizeof(n_values) / sizeof(n_values[0]);

    // Выводим таблицу 1: Сравнение ShellSort и InsertSort
    printTable1(n_values, size);

    // Выводим таблицу 2: Исследование зависимости от последовательности шагов
    //printTable2(n_values, size);

    return 0;
}