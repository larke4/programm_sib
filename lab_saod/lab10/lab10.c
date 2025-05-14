#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Глобальные счетчики операций
int actual_swaps = 0;    // Фактическое количество пересылок (M)
int actual_comparisons = 0; // Фактическое количество сравнений (C)

// Функция построения (L, R)-пирамиды
void buildHeap(int array[], int left, int right) {
    int parent = left;
    int child = 2 * left;
    int root_value = array[left - 1]; // В псевдокоде индексация с 1, у нас с 0
    actual_swaps++; // Сохранение корня

    while (child <= right) {
        actual_comparisons++; // Проверка child <= right
        if (child < right) {
            actual_comparisons++; // Сравнение дочерних элементов
            if (array[child - 1] < array[child]) {
                child++;
            }
        }
        
        actual_comparisons++; // Сравнение корня с наибольшим потомком
        if (root_value >= array[child - 1]) {
            break;
        }
        
        array[parent - 1] = array[child - 1];
        actual_swaps++; // Перемещение потомка вверх
        parent = child;
        child = 2 * parent;
    }
    
    array[parent - 1] = root_value;
    actual_swaps++; // Восстановление корня
}

// Пирамидальная сортировка
void heapSort(int array[], int size) {
    actual_swaps = 0;
    actual_comparisons = 0;
    
    // Построение пирамиды
    int start = size / 2;
    while (start > 0) {
        buildHeap(array, start, size);
        start--;
    }
    
    // Сортировка
    int end = size;
    while (end > 1) {
        // Обмен первого и последнего элементов
        int temp = array[0];
        array[0] = array[end - 1];
        array[end - 1] = temp;
        actual_swaps += 3; // 3 операции при обмене
        
        end--;
        buildHeap(array, 1, end);
    }
}

// Теоретические оценки трудоемкости
void theoreticalEstimates(int size, int *theoretical_comparisons, int *theoretical_swaps) {
    double log2_size = log2(size);
    *theoretical_comparisons = (int)(2 * size * log2_size + size + 2);
    *theoretical_swaps = (int)(size * log2_size + 6.5 * size - 4);
}

// Генерация массивов
void generateDecreasingArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i;
    }
}

void generateRandomArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

void generateIncreasingArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
}

int main() {
    srand(time(NULL));
    
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Трудоемкость пирамидальной сортировки\n");
    printf("| N    | Теория (C+M) | HeapSort (Мф+Сф) |\n");
    printf("|      |              | Убыв. | Возр. | Случ. |\n");
    printf("|------|--------------|-------|-------|-------|\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int *array = (int *)malloc(size * sizeof(int));
        int theoretical_comparisons, theoretical_swaps;
        
        theoreticalEstimates(size, &theoretical_comparisons, &theoretical_swaps);
        int total_theoretical = theoretical_comparisons + theoretical_swaps;
        
        // Убывающий массив
        generateDecreasingArray(array, size);
        heapSort(array, size);
        int decreasing_total = actual_swaps + actual_comparisons;
        
        // Возрастающий массив
        generateIncreasingArray(array, size);
        heapSort(array, size);
        int increasing_total = actual_swaps + actual_comparisons;
        
        // Случайный массив
        generateRandomArray(array, size);
        heapSort(array, size);
        int random_total = actual_swaps + actual_comparisons;
        
        printf("| %-4d | %-12d | %-5d | %-5d | %-5d |\n", 
               size, total_theoretical, decreasing_total, increasing_total, random_total);
        
        free(array);
    }
    
    return 0;
}