#include "event.h"
#include "uart_fsm.h"
#include "button.h"
#include "ring_buffer.h"
#include "timer.h"
#include "enum_def.h"

#define BUTTON_STREAM_LENGTH 7

int main()
{
    char uart_stream[] = "LEDON\nLED OFF\nSTATUS\n";
    int button_stream[] = {0,1,0,1,1,1,0};

    char *ptr = uart_stream;

    Event e_uart, e_button, e_timer, e;
    RingBuffer queue;

    int tick_val = 0;

    rb_init(&queue);

    while(1)
    {
        if(*ptr)
        {
            e_uart = process_char(*ptr);
            if(e_uart != EVENT_NONE)
            {
                if(rb_push(&queue, e_uart) < 0)
                    printf("Queue Full\n");
                else
                    printf("Event Added\n");
            }
            ptr++;
        }

        if(tick_val < BUTTON_STREAM_LENGTH)
        {
            e_button = process_button(button_stream[tick_val]);
            if(e_button != EVENT_NONE)
            {
                if(rb_push(&queue, e_button) < 0)
                    printf("Queue Full\n");
                else
                    printf("Event Added\n");
            }
        }

        e_timer = process_timer(tick_val);
        if(e_timer != EVENT_NONE)
        {
            if(rb_push(&queue, e_timer) < 0)
                printf("Queue Full\n");
            else
                printf("Event Added\n");
        }

        while(rb_pop(&queue, &e) == 0)
        {
            handle_event(e);
        }

        tick_val++;

        //Only because I am not running on actual hardware
        if(tick_val == 25)
            break;

    }

    return 0;
}