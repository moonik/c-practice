#ifndef PROJECT_BST_H
#define PROJECT_BST_H

typedef struct Node Node;
struct Node {
    int key;
    int value;
};

struct Heap {
    int n;
    Node **nodes;
};

typedef struct Heap Heap;

Heap *new();
void insert(Heap *heap, int k, int v);
void siftUp(Heap *heap, int k);
void swap(Heap *heap, int i, int j);
int getMax(Heap *heap);
int extractMax(Heap *heap);
void siftDown(Heap *heap, int k, int n);
void removeNode(Heap *heap, int i);
void heapify(int *arr, int n);
void sort(int *arr, int n);
void sink(int *arr, int k, int n);

#endif //PROJECT_BST_H
