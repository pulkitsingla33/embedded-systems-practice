#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdio.h>
#include <stdint.h>
#include "enum_def.h"

#define SIZE 16

typedef struct
{
    uint8_t buffer[SIZE];
    uint8_t head;
    uint8_t tail;
} RingBuffer;

void rb_init(RingBuffer *rb);
int rb_push(RingBuffer *rb, Event data);
int rb_pop(RingBuffer *rb, Event *data);

#endif