#include <stdio.h>
#include "Heap.h"

int main() {
    Heap *heap = new();
    insert(heap, 5, 10);
    insert(heap, 8, 101);
    insert(heap, 2, 150);
    insert(heap, 10, 105);
    int arr[6] = {5, 1, 4, 3, 0, 2};
    sort(arr, 6);
    for (int i = 0; i < 6; ++i) {
        printf("%d\n", arr[i]);
    }
//    for (int i = 1; i <= n-1; ++i) {
//        printf("%d\n", heap->nodes[i]->key);
//    }
    //removeNode(heap, 2);
    //n = heap->n;
    //printf("Extracting max...\n");
//    for (int j = 0; j < n-1; ++j) {
//        printf("%d\n", extractMax(heap));
//    }
}