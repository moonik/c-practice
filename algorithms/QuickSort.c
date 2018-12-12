#include <assert.h>
#include <stdio.h>

int doPartition(int* arr, int left, int right, int pivot) {
    int l = left;
    int r = right;

    while (l <= r) {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            int tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
    }
    return l;
}

void qsort_(int* arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = arr[left + (right-left) / 2];
    int p = doPartition(arr, left, right, pivot);

    qsort_(arr, left, p-1);
    qsort_(arr, p, right);
}

void quickSort(int* arr, int n) {
    qsort_(arr, 0, n-1);
}

void quickSortTest() {
    printf("====> Running Quick Sort tests...\n");
    int arr[9] = {99, 7, 4, 34, 0, 2, 3, -11, 5};
    int n = sizeof(arr)/ sizeof(arr[0]);
    quickSort(arr, n);
    int expected[9] = {-11, 0, 2, 3, 4, 5, 7, 34, 99};
    for (int i = 0; i < n; ++i) {
        printf("%d==%d\n", arr[i], expected[i]);
        assert(arr[i] == expected[i]);
    }
    printf("====> Quick Sort passed!\n");
}
