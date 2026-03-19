/*
Lock-free Ring-Buffer implementation in C for Embedded Systems
This implementation always leaves one slot empty to differentiate between full and empty states,
    thus the effective capacity is SIZE - 1.
It helps to avoid the need for additional flags to track the state of the buffer, simplifying the logic and improving performance.
It also prevents race conditions in concurrent environments, as the head and tail pointers are updated atomically without needing locks.
*/

#include <stdint.h>
#include <stdio.h>

#define SIZE 16

typedef struct
{
    uint8_t buffer[SIZE];
    uint8_t head;
    uint8_t tail;
} RingBuffer;

void rb_init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

int rb_push(RingBuffer *rb, uint8_t data)
{
    uint8_t next = (rb->tail + 1) & (SIZE - 1);

    if(next == rb->head)
    {
        printf("Cannot Push. Buffer full\n");
        return -1; // full
    }

    rb->buffer[rb->tail] = data;
    printf("Push %d at: %d\n", data, rb->tail);

    rb->tail = next;

    return 0;
}

int rb_pop(RingBuffer *rb, uint8_t *data)
{
    if(rb->head == rb->tail)
    {
        printf("Cannot Pop. buffer Empty");
        return -1; // empty
    }

    *data = rb->buffer[rb->head];
    printf("Pop %d from %d\n", *data, rb->head);

    rb->head = (rb->head + 1) & (SIZE - 1);

    return 0;
}