#include <stdlib.h>
#include "Queue.h"

Queue* new() {
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void destroy(Queue *queue) {
    Node *current = queue->head;
    Node *next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

void enqueue(Queue *queue, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (empty(queue)) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

int dequeue(Queue *queue) {
    if (empty(queue)) {
        exit(EXIT_FAILURE);
    }
    int value = queue->head->data;
    Node *tmp = queue->head;
    queue->head = queue->head->next;
    free(tmp);
    return value;
}

bool empty(Queue *queue) {
    return queue->head == NULL;
}