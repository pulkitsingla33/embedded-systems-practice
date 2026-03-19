#include "../Day_3/ring_buffer_corrected.c"
#include <stdio.h>
#include <stdint.h>

void process_data(RingBuffer *rb)
{
    uint8_t data = 0;;
    rb_pop(rb, &data);

    if(data & 0x01)
        printf("Number is: %d, Odd\n", data);
    else
        printf("Number is: %d, Even\n", data);
}

int main(int argc, char *argv[])
{
    RingBuffer rb;
    rb_init(&rb);
    
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j<3; j++)
        {
            rb_push(&rb, (i*5 + j));
        }
        process_data(&rb);
    }

    return 0;
}