#include <assert.h>
#include <stdio.h>

void merge(int* arr, int* aux, int leftStart, int mid, int rightEnd) {
    int l = leftStart;
    int r = mid+1;
    int i = leftStart;

    while (l <= mid && r <= rightEnd) {
        if (arr[l] < arr[r]) {
            aux[i++] = arr[l++];
        } else
            aux[i++] = arr[r++];
    }

    while (l <= mid) {
        aux[i++] = arr[l++];
    }
    while (r <= rightEnd) {
        aux[i++] = arr[r++];
    }
    while (leftStart <= rightEnd) {
        arr[leftStart] = aux[leftStart];
        leftStart++;
    }
}

void mergeSort(int* arr, int* aux, int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = l + (r - l) / 2;

    mergeSort(arr, aux, l, mid);
    mergeSort(arr, aux, mid+1, r);
    merge(arr, aux, l, mid, r);
}

void sort_(int* arr, int size) {
    int aux[size];
    mergeSort(arr, aux, 0, size-1);
}

void mergeSortTest() {
    printf("Running Merge Sort tests...\n");
    int arr[9] = {99, 7, 4, 34, 0, 2, 3, -11, 5};
    int n = sizeof(arr)/ sizeof(arr[0]);
    sort_(arr, n);
    int expected[9] = {-11, 0, 2, 3, 4, 5, 7, 34, 99};
    for (int i = 0; i < n; ++i) {
        printf("%d==%d\n", arr[i], expected[i]);
        assert(arr[i] == expected[i]);
    }
    printf("Merge Sort passed!\n");
}