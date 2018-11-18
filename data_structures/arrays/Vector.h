#ifndef C_PRACTICE_VECTOR_H
#define C_PRACTICE_VECTOR_H

#include <assert.h>
#include <stdbool.h>

static int __initialCapacity = 16;

typedef struct VectorArray {
    int size;
    int capacity;
    int *data; // int *data = int data[]
} Vector;

Vector* new();
Vector* newWithCapcity(int capacity);
void destroy(Vector *vector);

void __resize(Vector *vector, int size);
int __determineCapacity(int capacity);

/**
 *
 * @return number of items
 */
int size(Vector *vector);

/**
 *
 * @return current capacity
 */
int capacity(Vector *vector);

/**
 *
 * @return state of the vector(true if empty)
 */
bool isEmpty(Vector *vector);

/**
 * returns item at given index
 * @param index
 * @return
 */
int at(Vector *vector, int index);

/**
 * appends item to the end
 * @param item
 */
void push(Vector *vector, int item);

/**
 * inserts item at index,
 * shifts that index's value and trailing elements to the right
 * @param index
 * @param item
 */
void insert(Vector *vector, int index, int item);

/**
 * can use insert above at index 0
 */
void prepend(Vector *vector, int item);

/**
 * remove from end, return value
 * @return
 */
int pop(Vector *vector);

/**
 * delete item at index, shifting all trailing elements left
 * @param vector
 * @param index
 */
void delete(Vector *vector, int index);

/**
 * looks for value and removes index holding it (even if in multiple places)
 * @param vector
 * @param item
 */
void removeItem(Vector *vector, int item);

/**
 * looks for value and returns first index with that value, -1 if not found
 * @param vector
 * @param item
 * @return
 */
int find(Vector *vector, int item);


/**
 * TEST SECTION
 */

Vector* __createVector();
void runTests();
void should_intialize_with_default_capacity();
void should_initialize_with_provided_capacity_and_round_up();
void should_resize_array();
void should_push_item();
void should_return_item_at_index();
void should_insert_at_index();
void should_prepend();
void should_pop();
void should_delete();
void should_remove_all_items();
void should_return_item();

#endif //C_PRACTICE_VECTOR_H
