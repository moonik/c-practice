#ifndef C_PRACTICE_NODE_H
#define C_PRACTICE_NODE_H

#include <stdbool.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} List;

List* new();
void destroy(List *list);

/*
 * returns number of data elements in list
 */
int size(List *list);

/*
 * returns true if empty
 */
bool empty(List *list);

/*
 * returns the value of the nth item (starting at 0 for first)
 */
int valueAt(List *list, int index);

/*
 * adds an item to the front of the list
 */
void pushFront(List *list, int value);

/*
 * remove front item and return its value
 */
int popFront(List *list);

/*
 * adds an item at the end
 */
void pushBack(List *list, int value);

/*
 * removes end item and returns its value
 */
int popBack(List *list);

/*
 * get value of front item
 */
int front(List *list);

/*
 * get value of end item
 */
int back(List *list);

/*
 * insert value at index, so current item at that index is pointed to by new item at index
 */
void insert(List *list, int index, int value);

/*
 * removes node at given index
 */
void erase(List *list, int index);

/*
 * returns the value of the node at nth position from the end of the list
 */
int valueNfromEnd(List *list, int n);

/*
 * reverses the list
 */
void reverse(List *list);

/*
 * removes the first item in the list with this value
 */
void removeValue(List *list, int value);


/*
 * TESTS
 */
void runAllTests();
void should_push_to_the_front();
void should_pop_front();
void should_push_back();
void should_pop_back();
void should_insert_at_index_value();
void should_erase_at_index();
void should_return_value_n_from_end();
void should_reverse();
void should_remove_value();

#endif //C_PRACTICE_NODE_H
