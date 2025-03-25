#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool binary_search_v1(int arr[], int n, int key, int *comparisons, int *position) {
    int L = 0, R = n - 1;
    bool found = false;

    while (L <= R) {
        int m = (L + R) / 2;

        (*comparisons)++; 
        if (arr[m] == key) {
            found = true;
            *position = m;
            break;
        }

        (*comparisons)++; 
        if (arr[m] < key) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }

    return found;
}

bool binary_search_v2(int arr[], int n, int key, int *comparisons, int *position) {
    int L = 0, R = n - 1;
    bool found = false;

    while (L < R) {
        int m = (L + R) / 2;

        (*comparisons)++; 
        if (arr[m] < key) {
            L = m + 1;
        } else {
            R = m;
        }
    }

    (*comparisons)++; 
    if (arr[L] == key) {
        found = true;
        *position = L;
    }

    return found;
}

// Функция для вычисления теоретического количества сравнений
int theoretical_v1(int n) {
    return 2 * (int)ceil(log2(n)); // 2 * log2(n), округленное вверх
}

int theoretical_v2(int n) {
    return (int)ceil(log2(n)) + 1; // log2(n) + 1, округленное вверх
}

int main() {
    const int n = 1000;
    int arr[n];

    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    int key;
    int comparisons_v1 = 0, comparisons_v2 = 0;
    int position_v1 = -1, position_v2 = -1;

    printf("Введите ключ поиска (от 1 до 1000): ");
    scanf("%d", &key);

    bool found_v1 = binary_search_v1(arr, n, key, &comparisons_v1, &position_v1);
    if (found_v1) {
        printf("Версия 1: Элемент %d найден на позиции %d, количество сравнений: %d\n", key, position_v1, comparisons_v1);
    } else {
        printf("Версия 1: Элемент не найден, количество сравнений: %d\n", comparisons_v1);
    }

    bool found_v2 = binary_search_v2(arr, n, key, &comparisons_v2, &position_v2);
    if (found_v2) {
        printf("Версия 2: Элемент %d найден на позиции %d, количество сравнений: %d\n", key, position_v2, comparisons_v2);
    } else {
        printf("Версия 2: Элемент не найден, количество сравнений: %d\n", comparisons_v2);
    }

    printf("\nТрудоемкость двоичного поиска элемента\n");
    printf("+-----+-----------+------------+\n");
    printf("|  N  | Сф I версия| Сф II версия|\n");
    printf("+-----+-----------+------------+\n");
    for (int i = 100; i <= 1000; i += 100) {
        int c1 = theoretical_v1(i);
        int c2 = theoretical_v2(i); 

        printf("|%5d|%12d|%13d|\n", i, c1, c2);
    }
    printf("+-----+-----------+------------+\n");

    return 0;
}