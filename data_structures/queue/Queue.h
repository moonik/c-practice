#ifndef C_PRACTICE_QUEUE_H
#define C_PRACTICE_QUEUE_H

#include <stdbool.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

Queue* new();
void destroy(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
bool empty(Queue *queue);

#endif //C_PRACTICE_QUEUE_H
