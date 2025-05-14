#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "matrix_multiply.h"

typedef struct {
    int start_row;
    int end_row;
    double (*A)[N];
    double (*B)[N];
    double (*C)[N];
} MatrixArgs;

void* multiply_part(void* arg) {
    MatrixArgs* args = (MatrixArgs*)arg;
    for (int i = args->start_row; i < args->end_row; i++) {
        for (int j = 0; j < N; j++) {
            args->C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                args->C[i][j] += args->A[i][k] * args->B[k][j];
            }
        }
    }
    return NULL;
}

void parallel_matrix_multiply(int N, int num_threads) {
    // Выделение памяти и инициализация матриц
    pthread_t threads[num_threads];
    MatrixArgs args[num_threads];
    
    // Создание потоков
    for (int i = 0; i < num_threads; i++) {
        // Настройка аргументов для каждого потока
        pthread_create(&threads[i], NULL, multiply_part, &args[i]);
    }
    
    // Ожидание завершения
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}