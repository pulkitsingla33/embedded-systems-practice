#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t buffer[16];
    uint8_t head;
    uint8_t tail;
} RingBuffer;

void rb_init(RingBuffer *rb);
int rb_push(RingBuffer *rb, uint8_t data);
int rb_pop(RingBuffer *rb);

void rb_init(RingBuffer *rb)
{
    rb->head = 0xFF;
    rb->tail = 0xFF;
    printf("Initialization Done!\n");
}

int rb_push(RingBuffer *rb, uint8_t data)
{
    if((rb->tail == 0xFF))
    {
        
        if(rb->head == 0xFF)
        {
            rb->tail = 0;
            rb->head = 0;
        }
        else
        {
            rb->tail = rb->head;
        }        
    }
    else
    {
        if((rb->head == 0 && rb->tail == 15) || (rb->head - rb->tail == 1))
        {
            printf("Buffer Full\n");
            return -1;
        }
        else
        {
            if(rb->tail == 15)
                rb->tail = 0;
            else
                rb->tail += 1;
        }   
    }
    
    rb->buffer[rb->tail] = data;
    printf("Push %d at position: %d\n", data, rb->tail);
    return 0;
}

int rb_pop(RingBuffer *rb)
{
    uint8_t pop_data = 0;

    if(rb->tail == 0xFF)
    {
        printf("Buffer Empty\n");
        return -1;
    }
    else
    {
        pop_data = rb->buffer[rb->head];

        if(rb->head == rb->tail)
            rb->tail = 0xFF;

        printf("Pop %d from location: %d\n", pop_data, rb->head);
        
        if(rb->head == 15)
            rb->head = 0;
        else
            rb->head += 1;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    RingBuffer rb;

    rb_init(&rb);

    for(int i = 0; i < 5; i++)
    {
        rb_push(&rb, i);        
    }

    for(int i = 0; i < 2; i++)
    {
        rb_pop(&rb);        
    }

    for(int i = 0; i < 12; i++)
    {
        rb_push(&rb, i);        
    }

    for(int i = 0; i < 5; i++)
    {
        rb_pop(&rb);        
    }


    return 0;
}