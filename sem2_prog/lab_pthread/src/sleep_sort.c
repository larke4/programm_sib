#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* sleep_sort_thread(void* arg) {
    int val = *(int*)arg;
    sleep(val);
    printf("%d ", val);
    return NULL;
}

void sleep_sort(int arr[], int n) {
    pthread_t threads[n];
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort_thread, &arr[i]);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
}