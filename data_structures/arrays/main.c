#include <stdio.h>
#include "Vector.h"

void print(Vector *vector) {
    for (int k = 0; k < size(vector); ++k) {
        printf("%d\n", vector->data[k]);
    }
}

int main() {
    runTests();
    Vector *vector = new();

    for (int i = 0; i < 17; ++i) {
        push(vector, i);
    }

    printf("Inserted items: \n");
    print(vector);

    for (int j = 0; j < 5; ++j) {
        delete(vector, j);
    }

    printf("Items after deletion: \n");
    print(vector);

    removeItem(vector, 10);
    removeItem(vector, 6);

    printf("Removed 10 and 6\n");
    print(vector);

    prepend(vector, 4837593);
    printf("Prepended 4837593\n");
    print(vector);

    pop(vector);
    printf("Popped 16\n");
    print(vector);

    insert(vector, 0, -99);
    insert(vector, 5, -4584758);
    printf("Inserted -99 and -4584758\n");
    print(vector);
}