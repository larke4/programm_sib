#include <string.h>
#include <pthread.h>
#include "message_queue.h"

void queue_init(MessageQueue* q) {
    q->front = q->rear = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

int msgSend(MessageQueue* q, const char* msg) {
    pthread_mutex_lock(&q->mutex);
    while ((q->rear + 1) % 10 == q->front) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    strncpy(q->messages[q->rear], msg, 128);
    q->rear = (q->rear + 1) % 10;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    return strlen(msg);
}