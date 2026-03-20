#include <stdio.h>
#include <stdint.h>
#include "../Day_3/ring_buffer_corrected.c"

#define BUTTON_STREAM_LENGTH 6
#define DEBOUNCE_THRESHOLD 3

typedef enum
{
    IDLE,
    LED0,
    LED1,
    LED2,
    SPACE,
    LED_O,
    ON1,
    OFF1,
    OFF2,
    STAT0,
    STAT1,
    STAT2,
    STAT3,
    STAT4,
    STAT5
} UART_State;

typedef enum
{
    EVENT_NONE,
    EVENT_LED_ON,
    EVENT_LED_OFF,
    EVENT_STATUS,
    EVENT_BUTTON_PRESS,
    EVENT_TIMEOUT
} Event;

Event process_char(char c);
Event process_button(int input);
Event process_timer(int tick);
void handle_event(Event e);

Event process_char(char c)
{
    static UART_State current_state = IDLE;

    if((c == '\n') && ((current_state != ON1) && (current_state != OFF2) && (current_state != STAT5)))
        return EVENT_NONE;

    switch(current_state)
    {
        case IDLE:  if(c == 'L')
                        current_state = LED0;
                    else if(c == 'S')
                        current_state = STAT0;
                    else
                        current_state = IDLE;
                break;

        case LED0:  if(c == 'E')
                        current_state = LED1;
                    else
                        current_state = IDLE;
                break;

        case LED1:  if(c == 'D')
                        current_state = LED2;
                    else
                        current_state = IDLE;
                break;

        case LED2:  if(c == ' ')
                        current_state = SPACE;
                    else
                        current_state = IDLE;
                break;

        case SPACE: if(c == 'O')
                        current_state = LED_O;
                    else
                        current_state = IDLE;
                break;
        
        case LED_O: if(c == 'N')
                        current_state = ON1;
                    else if(c == 'F')
                        current_state = OFF1;
                    else
                        current_state = IDLE;
                break;
        
        case ON1:   current_state = IDLE;
                    if(c == '\n')
                        return EVENT_LED_ON;
                break;

        case OFF1:  if(c == 'F')
                        current_state = OFF2;
                    else
                        current_state = IDLE;
                break;

        case OFF2:  current_state = IDLE;
                    if(c == '\n')
                        return EVENT_LED_OFF;
                break;

        case STAT0: if(c == 'T')
                        current_state = STAT1;
                    else
                        current_state = IDLE;
                break;

        case STAT1: if(c == 'A')
                        current_state = STAT2;
                    else
                        current_state = IDLE;
                break;

        case STAT2: if(c == 'T')
                        current_state = STAT3;
                    else
                        current_state = IDLE;
                break;

        case STAT3: if(c == 'U')
                        current_state = STAT4;
                    else
                        current_state = IDLE;
                break;

        case STAT4: if(c == 'S')
                        current_state = STAT5;
                    else
                        current_state = IDLE;
                break;

        case STAT5:  current_state = IDLE;
                    if(c == '\n')
                        return EVENT_STATUS;
                break;
        
        default:    current_state = IDLE;   
    }

    return EVENT_NONE;
}

Event process_button(int input)
{
    static int count = 0;
    static int triggered = 0;

    if(input == 0)
    {
        triggered = 0;
        count = 0;
    }
    else
    { 
        if (count < DEBOUNCE_THRESHOLD)
                count++;

        if(count == DEBOUNCE_THRESHOLD && !triggered)
        {
            triggered = 1;
            return EVENT_BUTTON_PRESS;
        }
    }
    
    return EVENT_NONE;
}

Event process_timer(int tick)
{
    if((tick != 0) && (tick % 5 == 0))
        return EVENT_TIMEOUT;

    return EVENT_NONE;
}

void handle_event(Event e)
{
    switch(e)
    {
        case EVENT_LED_ON:
            printf("LED ON\n");
            break;

        case EVENT_LED_OFF:
            printf("LED OFF\n");
            break;

        case EVENT_STATUS:
            printf("STATUS\n");
            break;

        case EVENT_BUTTON_PRESS:
            printf("BUTTON PRESS\n");
            break;

        case EVENT_TIMEOUT:
            printf("TIMEOUT\n");
            break;

        default:
            break;
    }
}

int main(int argc, char *argv[])
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