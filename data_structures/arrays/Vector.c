#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

Vector* new() {
    Vector *arr = malloc(sizeof(Vector));
    arr->size = 0;
    arr->capacity = __initialCapacity;
    arr->data = (int*) malloc(sizeof(int)*__initialCapacity);
    return arr;
}

Vector* newWithCapcity(int size) {
    int capacity = __determineCapacity(size);
    Vector *arr = malloc(sizeof(Vector));
    arr->size = 0;
    arr->capacity = capacity;
    arr->data = (int*) malloc(sizeof(int)*capacity);
    return arr;
}

void destroy(Vector *vector) {
    free(vector->data);
    free(vector);
}

void __resize(Vector *vector, int size) {
    int oldSize = vector->size;
    int *data = (int*) malloc(sizeof(int)*size);

    for (int i = 0; i < oldSize; ++i) {
        data[i] = vector->data[i];
    }

    free(vector->data);
    vector->data = data;
    vector->capacity = size;
}

int size(Vector *vector) {
    return vector->size;
}

int capacity(Vector *vector) {
    return vector->capacity;
}

bool isEmpty(Vector *vector) {
    return vector->size == 0;
}

int at(Vector *vector, int index) {
    if (index > -1 && index <= vector->size) {
        return vector->data[index]; // the same as *(vector->data + index)
    } else
        exit(EXIT_FAILURE);
}

void push(Vector *vector, int item) {
    if (vector == NULL) {
        exit(EXIT_FAILURE);
    }
    if (vector->size >= vector->capacity) {
        __resize(vector, __determineCapacity(vector->size * 2));
    }
    vector->data[vector->size++] = item;
}

void insert(Vector *vector, int index, int item) {
    if (vector == NULL || index < 0 || index >= vector->capacity) {
        exit(EXIT_FAILURE);
    }

    if (vector->size+1 >= vector->capacity) {
        __resize(vector, __determineCapacity(vector->capacity*2));
    }

    for (int i = vector->size; i > index; --i) {
        vector->data[i] = vector->data[i-1];
    }

    vector->data[index] = item;
    vector->size++;
}

void prepend(Vector *vector, int item) {
    if (vector->size == 0) {
        vector->data[0] = item;
    } else {
        if (vector->size+1 >= vector->capacity) {
            __resize(vector, __determineCapacity(vector->capacity*2));
        }
        for (int i = vector->size; i > 0; --i) {
            vector->data[i] = vector->data[i-1];
        }
    }
    vector->data[0] = item;
    vector->size++;
}

int pop(Vector *vector) {
    if (vector->size == 0) {
        exit(EXIT_FAILURE);
    }
    return vector->data[--vector->size];
}

void delete(Vector *vector, int index) {
    if (index < 0 || index > vector->size) {
        exit(EXIT_FAILURE);
    }
    for (int i = index; i < vector->size; ++i) {
        vector->data[i] = vector->data[i+1];
    }
    vector->size--;
}

void removeItem(Vector *vector, int item) {
    for (int i = 0; i < vector->size; ++i) {
        if (vector->data[i] == item) {
            delete(vector, i);
        }
    }
}

int find(Vector *vector, int item) {
    for (int i = 0; i < vector->size; ++i) {
        if (vector->data[i] == item) {
            return i;
        }
    }
    return -1;
}

int __determineCapacity(int size) {
    if (size % 2 == 0 && size > 16) {
        return size;
    } else {
        size--;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        return ++size;
    }
}


/**
 * TESTS
 */

Vector* __createVector() {
    Vector *vector = new();
    for (int i = 0; i < 14; ++i) {
        push(vector, i);
    }
    push(vector, 989);
    return vector;
}

void runTests() {
    should_intialize_with_default_capacity();
    should_initialize_with_provided_capacity_and_round_up();
    should_resize_array();
    should_push_item();
    should_return_item_at_index();
    should_insert_at_index();
    should_prepend();
    should_pop();
    should_delete();
    should_remove_all_items();
    should_return_item();
}

void should_intialize_with_default_capacity() {
    //given
    Vector *vector;

    //when
    vector = new();

    //then
    assert(vector != NULL);
    assert(capacity(vector) == __initialCapacity);
    destroy(vector);
}

void should_initialize_with_provided_capacity_and_round_up() {
    //given
    Vector *vector;
    int expectedCapacity = 16;
    int proviedCapacity = 14;

    //when
    vector = newWithCapcity(proviedCapacity);

    //then
    assert(vector != NULL);
    assert(expectedCapacity == capacity(vector));
    destroy(vector);
}

void should_resize_array() {
    //given
    Vector *vector = __createVector();

    //when
    for (int i = 0; i < 10; ++i) {
        push(vector, i);
    }

    //then
    assert(capacity(vector) == 32);
    destroy(vector);
}

void should_push_item() {
    //given
    Vector *vector = new();
    //when
    push(vector, 1);
    push(vector, 2);

    //then
    assert(isEmpty(vector) == false);
    assert(size(vector) == 2);
    destroy(vector);
}

void should_return_item_at_index() {
    //given
    Vector *vector = __createVector();
    int expectedItem = 4;
    int index = 4;

    //when
    int actualItem = at(vector, index);

    //then
    assert(expectedItem == actualItem);
    destroy(vector);
}

void should_insert_at_index() {
    //given
    Vector *vector = __createVector();
    int item = 99;
    int item2 = 96;
    int expectedSize = size(vector) + 2;

    //when
    insert(vector, 2, item);
    insert(vector, 15, item2);

    //then
    assert(at(vector, 2) == item);
    assert(at(vector, 15) == item2);
    assert(expectedSize == size(vector));
    destroy(vector);
}

void should_prepend() {
    //given
    Vector *vector = __createVector();
    int item = -99;

    //when
    prepend(vector, item);

    //then
    assert(at(vector, 0) == item);
    assert(at(vector, 1) == 0);
    destroy(vector);
}

void should_pop() {
    //given
    Vector *vector = __createVector();
    int expected = 989;

    //when
    int actual = pop(vector);

    //then
    assert(actual == expected);
    destroy(vector);
}

void should_delete() {
    //given
    Vector *vector = __createVector();
    int index = 5;
    int expectedValueAtIndex = 6;
    int initialSize = vector->size;

    //when
    delete(vector, index);

    //then
    assert(at(vector, index) == expectedValueAtIndex);
    assert(size(vector) == initialSize-1);
    destroy(vector);
}

void should_remove_all_items() {
    //given
    Vector *vector = __createVector();
    int itemToremove = 0;

    //when
    removeItem(vector, itemToremove);

    //then
    assert(find(vector, itemToremove) == -1);
    destroy(vector);
}

void should_return_item() {
    //given
    Vector *vector = __createVector();
    int item = 4;
    int expectedIndex = 4;

    //when
    int actual = find(vector, item);

    //then
    assert(actual == expectedIndex);
    destroy(vector);
}