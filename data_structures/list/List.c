#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

List* new() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void destroy(List *list) {
   Node *current = list->head;
   Node *next = NULL;

   while (current) {
      next = current->next;
      free(current);
      current = next;
   }
   free(list);
}

int valueAt(List *list, int index) {
   Node *n = list->head;
   while (n != NULL && index > 0) {
      index--;
      n = n->next;
   }
   if (n == NULL) {
      exit(EXIT_FAILURE);
   } else
      return n->data;
}

void pushFront(List *list, int value) {
   Node *newNode = malloc(sizeof(Node));
   newNode->next = list->head;
   newNode->data = value;
   list->head = newNode;
   if (list->tail == NULL) {
      list->tail = newNode;
   }
}

int popFront(List *list) {
   int v = list->head->data;
   Node *tmp = list->head;
   list->head = list->head->next;
   if (list->head == NULL) {
      list->tail = NULL;
   }
   free(tmp);
   return v;
}

void pushBack(List *list, int value) {
   Node *n = malloc(sizeof(Node));
   n->data = value;
   n->next = NULL;
   if (list->head == NULL) {
      list->head = list->tail = n;
   } else {
      list->tail->next = n;
      list->tail = n;
   }
}

int popBack(List *list) {
   if (list-> tail == NULL) {
      exit(EXIT_FAILURE);
   }
   Node *current = list->head;
   Node *prev = NULL;

   while (current->next != NULL) {
      prev = current;
      current = current->next;
   }

   int v = current->data;
   prev->next = NULL;
   list->tail = prev;
   free(current);
   return v;
}

int front(List *list) {
   return list->head->data;
}

int back(List *list) {
   return list->tail->data;
}

void insert(List *list, int index, int value) {
   if (index == 0) {
      pushFront(list, value);
      return;
   }

   Node *current = list->head;
   Node *prev = NULL;

   while (current != NULL && index > 0) {
      prev = current;
      current = current->next;
      index--;
   }

   if (current == NULL && index != 0) {
      printf("Index out of bounds");
      exit(EXIT_FAILURE);
   }

   Node *newNode = malloc(sizeof(Node));
   newNode->data = value;

   prev->next = newNode;
   newNode->next = current;
}

void erase(List *list, int index) {
   if (index == 0) {
      popFront(list);
      return;
   }

   Node *current = list->head;
   Node *prev = NULL;

   while (current != NULL && index > 0) {
      prev = current;
      current = current->next;
      index--;
   }

   if (current == NULL && index != 0) {
      printf("Index out of bounds");
      exit(EXIT_FAILURE);
   }
   prev->next = current->next;
   free(current);
}

int valueNfromEnd(List *list, int n) {
   if (n == 0) {
      return back(list);
   }
   Node *next = list->head;
   while (n > 0 && next != NULL) {
      next = next->next;
      n--;
   }

   if (next == NULL && n > 0) {
      printf("Index out of bounds");
      exit(EXIT_FAILURE);
   }

   Node *current = list->head;

   while (next->next != NULL) {
      current = current->next;
      next = next->next;
   }

   return current->data;
}

void reverse(List *list) {
   Node *current = list->head;
   Node *prev = NULL;
   Node *next = NULL;

   list->tail = list->head;

   while (current != NULL) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
   }
   list->head = prev;
}

void removeValue(List *list, int value) {
   if (list->head->data == value) {
      popFront(list);
      return;
   }

   Node *current = list->head;
   Node *prev = NULL;

   while (current != NULL) {
      if (current->data == value) {
         prev->next = current->next;
         if (prev->next == NULL) {
            list->tail = prev;
         }
         free(current);
         return;
      }
      prev = current;
      current = current->next;
   }
}

/*
 * TESTS
 */

void runAllTests() {
   should_push_to_the_front();
   should_pop_front();
   should_push_back();
   should_pop_back();
   should_insert_at_index_value();
   should_erase_at_index();
   should_return_value_n_from_end();
   should_reverse();
   should_remove_value();
}

void should_push_to_the_front() {
   //given
   List *list = new();
   int expectedValue = 2;

   //when
   pushFront(list, 1);
   pushFront(list, 2);

   //then
   assert(valueAt(list, 0) == expectedValue);
   destroy(list);
}

void should_pop_front() {
   //given
   List *list = new();
   int expectedValue = 2;

   //and
   pushFront(list, 1);
   pushFront(list, 2);

   //when
   int actual = popFront(list);

   //then
   assert(expectedValue == actual);
   destroy(list);
}

void should_push_back() {
   //given
   List *list = new();

   //when
   pushBack(list, 1);
   pushBack(list, 2);

   //then
   for (int i = 1; i < 3; ++i) {
      assert(i == valueAt(list, i-1));
   }
   destroy(list);
}

void should_pop_back() {
   //given
   List *list = new();
   int expectedValue = 2;

   //and
   pushBack(list, 1);
   pushBack(list, 2);

   //when
   int actualValue = popBack(list);

   //then
   assert(actualValue == expectedValue);
   destroy(list);
}

void should_insert_at_index_value() {
   //given
   List *list = new();
   int index = 3;

   //and
   pushBack(list, 1);
   pushBack(list, 2);
   pushBack(list, 3);
   pushBack(list, 4);

   //when
   insert(list, index, 99);

   //then
   assert(valueAt(list, 3) == 99);
   assert(valueAt(list, 4) == 4);
   destroy(list);
}

void should_erase_at_index() {
   //given
   List *list = new();
   int index = 2;

   //and
   pushBack(list, 1);
   pushBack(list, 2);
   pushBack(list, 3);
   pushBack(list, 4);

   //when
   erase(list, index);

   //then
   assert(valueAt(list, index) == 4);
   destroy(list);
}

void should_return_value_n_from_end() {
   //given
   List *list = new();
   int n = 2;
   int expected = 2;

   //and
   pushBack(list, 1);
   pushBack(list, 2);
   pushBack(list, 3);
   pushBack(list, 4);

   //when
   int actual = valueNfromEnd(list, n);

   //then
   assert(expected == actual);
   destroy(list);
}

void should_reverse() {
   //given
   List *list = new();
   int n = 4;

   //and
   pushBack(list, 1);
   pushBack(list, 2);
   pushBack(list, 3);
   pushBack(list, 4);

   //when
   reverse(list);

   //then
   Node *current = list->head;
   while (n > 0) {
      assert(current->data == n);
      n--;
      current = current->next;
   }
   destroy(list);
}

void should_remove_value() {
   //given
   List *list = new();
   int value = 2;

   //and
   pushBack(list, 1);
   pushBack(list, 2);
   pushBack(list, 3);
   pushBack(list, 4);

   //when
   removeValue(list, value);

   //then
   assert(valueAt(list, 1) == 3);
   destroy(list);
}