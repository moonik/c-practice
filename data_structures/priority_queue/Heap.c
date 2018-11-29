#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"

Heap *new() {
    Heap *heap = malloc(sizeof(Heap));
    heap->n = 1;
    heap->nodes = (Node**) malloc(sizeof(Node)*10);
    return heap;
}

void insert(Heap *heap, int k, int v) {
    Node *n = malloc(sizeof(Node));
    n->key = k;
    n->value = v;
    heap->nodes[heap->n] = n;
    siftUp(heap, heap->n++);
}

int getMax(Heap *heap) {
    return heap->nodes[1]->key;
}

int extractMax(Heap *heap) {
    int max = heap->nodes[1]->key;
    swap(heap, 1, --heap->n);
    free(heap->nodes[heap->n]);
    heap->nodes[heap->n] = NULL;
    siftDown(heap, 1, heap->n);
    return max;
}

void removeNode(Heap *heap, int i) {
    Node *tmp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[--heap->n];
    heap->nodes[heap->n] = NULL;
    free(tmp);
    siftDown(heap, i, heap->n);
}

void heapify(int *arr, int n) {
    int k = n/2-1;
    for (; k >= 0; k--) {
        sink(arr, k, n);
    }
}

void sort(int *arr, int n) {
    heapify(arr, n);
    while (n > 0) {
        int tmp = arr[0];
        arr[0] = arr[n-1];
        arr[n-1] = tmp;
        sink(arr, 0, --n);
    }
    for (int i = 0; i < 6; ++i) {
        printf("%d\n", arr[i]);
    }
}

void sink(int *arr, int k, int n) {
    while (k*2+1 < n) {
        int j = k*2+1;
        if (j < n && (j+1) < n) {
            if (arr[j] < arr[j+1]) {
                j++;
            }
        }
        if (arr[k] >= arr[j]) {
            break;
        }
        int tmp = arr[k];
        arr[k] = arr[j];
        arr[j] = tmp;

        k = j;
    }
}

void siftDown(Heap *heap, int k, int n) {
    while (k*2 < n) {
        int j = k*2;
        if (heap->nodes[j] != NULL && heap->nodes[j+1] != NULL) {
            if (heap->nodes[j]->key < heap->nodes[j+1]->key) {
                j++;
            }
        }
        if (!(heap->nodes[k]->key < heap->nodes[j]->key)) {
            break;
        }
        swap(heap, k, j);
        k = j;
    }
}

void siftUp(Heap *heap, int k) {
    while (k > 1 && heap->nodes[k/2]->key < heap->nodes[k]->key) {
        swap(heap, k/2, k);
        k /= 2;
    }
}

void swap(Heap *heap, int i, int j) {
    Node *n = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = n;
}