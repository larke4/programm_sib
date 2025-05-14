#include "../include/queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void init_queue(MessageQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
}

void cleanup_queue(MessageQueue* queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->not_empty);
    pthread_cond_destroy(&queue->not_full);
}

int msgSend(MessageQueue* queue, const char* msg) {
    pthread_mutex_lock(&queue->mutex);
    
    while (queue->count >= MAX_QUEUE_SIZE) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }
    
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    strncpy(queue->items[queue->rear].message, msg, MAX_MSG_LENGTH - 1);
    queue->items[queue->rear].message[MAX_MSG_LENGTH - 1] = '\0';
    queue->count++;
    
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);
    
    return strlen(queue->items[queue->rear].message);
}

int msgRecv(MessageQueue* queue, char* buf, size_t bufsize) {
    pthread_mutex_lock(&queue->mutex);
    
    while (queue->count <= 0) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }
    
    QueueItem item = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->count--;
    
    size_t len = strlen(item.message);
    if (len > bufsize - 1) len = bufsize - 1;
    strncpy(buf, item.message, len);
    buf[len] = '\0';
    
    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);
    
    return len;
}

int msgDrop(MessageQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    pthread_cond_broadcast(&queue->not_empty);
    pthread_cond_broadcast(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);
    return 0;
}

void* server_thread(void* arg) {
    MessageQueue* queue = (MessageQueue*)arg;
    char client_name[20];
    snprintf(client_name, sizeof(client_name), "Server %ld", pthread_self() % 100);
    
    while (1) {
        char message[MAX_MSG_LENGTH];
        int len = msgRecv(queue, message, sizeof(message));
        if (len > 0) {
            printf("[%s] %s\n", client_name, message);
        }
        #ifdef _WIN32
        Sleep(rand() % 1000);  // Задержка в миллисекундах
#else
        usleep(rand() % 1000000);  // Оригинальный код для Unix
#endif
    }
    
    return NULL;
}

void* client_thread(void* arg) {
    MessageQueue* queue = (MessageQueue*)arg;
    char client_name[20];
    snprintf(client_name, sizeof(client_name), "Klient %ld", pthread_self() % 100);
    
    while (1) {
        char message[MAX_MSG_LENGTH];
        snprintf(message, sizeof(message), "Privet ot %s (%ld)", client_name, time(NULL));
        msgSend(queue, message);
        
        #ifdef _WIN32
        Sleep(10000);
    #else
        sleep(10);
    #endif
    }
    
    return NULL;
}

void demonstrate_message_queue() {
    printf("\n=== Ochered soobsheniy ===\n");
    printf("Zapusk serverov i klientov...\n");
    
    MessageQueue queue;
    init_queue(&queue);
    
    pthread_t servers[2];
    pthread_t clients[3];
    
    for (int i = 0; i < 2; i++) {
        pthread_create(&servers[i], NULL, server_thread, &queue);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&clients[i], NULL, client_thread, &queue);
    }
    
    #ifdef _WIN32
        Sleep(10000);
    #else
        sleep(10);
    #endif
    
    msgDrop(&queue);
    for (int i = 0; i < 2; i++) pthread_cancel(servers[i]);
    for (int i = 0; i < 3; i++) pthread_cancel(clients[i]);
    
    cleanup_queue(&queue);
}