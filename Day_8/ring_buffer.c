#include "ring_buffer.h"


void rb_init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

int rb_push(RingBuffer *rb, Event data)
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

int rb_pop(RingBuffer *rb, Event *data)
{
    if(rb->head == rb->tail)
    {
        printf("Cannot Pop. Buffer empty\n");
        return -1; // empty
    }

    *data = rb->buffer[rb->head];
    printf("Pop %d from %d\n", *data, rb->head);

    rb->head = (rb->head + 1) & (SIZE - 1);

    return 0;
}