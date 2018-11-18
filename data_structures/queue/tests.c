#include <assert.h>
#include "Queue.h"

void should_enqueue() {
    //given
    Queue *queue = new();

    //when
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    //then
    assert(empty(queue) == false);
    for (int i = 1; i <= 3; ++i) {
        assert(i == dequeue(queue));
    }
    destroy(queue);
}

void should_dequeue() {
    //given
    Queue *queue = new();

    //and
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    //when
    dequeue(queue);

    //then
    assert(empty(queue) == false);
    for (int i = 2; i <= 3; ++i) {
        assert(i == dequeue(queue));
    }
    destroy(queue);
}

void should_check_if_empty() {
    //given
    Queue *queue = new();

    //and
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    //when
    dequeue(queue);

    //then
    assert(empty(queue) == false);
    for (int i = 2; i <= 3; ++i) {
        assert(i == dequeue(queue));
    }
    assert(empty(queue) == true);
    destroy(queue);
}

void runQueueTests() {
    should_enqueue();
    should_dequeue();
    should_check_if_empty();
}