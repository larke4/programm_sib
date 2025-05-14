#include <pthread.h>
#include <stdio.h>
#include "pthread_basics.h"

// Задание 1-2: Создание и ожидание потока
void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i);
    }
    return NULL;
}

void basic_thread_example() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
}

// Задание 3: Параметры потока
typedef struct {
    int id;
    const char* messages[5];
} ThreadArgs;

void* param_thread_func(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: %s\n", args->id, args->messages[i]);
    }
    return NULL;
}

void param_threads_example() {
    pthread_t threads[4];
    ThreadArgs args[4];
    // Инициализация args
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, param_thread_func, &args[i]);
    }
    // ...
}