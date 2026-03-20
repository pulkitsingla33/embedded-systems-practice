typedef enum
{
    EVENT_NONE,
    EVENT_BUTTON_PRESS,
    EVENT_UART_CMD,
    EVENT_TIMEOUT
} Event;

void handle_event(Event e)
{
    switch(e)
    {
        case EVENT_NONE:
            printf("No Event\n");
            break;

        case EVENT_BUTTON_PRESS:
            printf("Button Pressed\n");
            break;

        case EVENT_UART_CMD:
            printf("UART Command Received\n");
            break;

        case EVENT_TIMEOUT:
            printf("Timeout Occurred\n");
            break;

        default:
            printf("Invalid Event\n");
    }
}

void process_events(RingBuffer *rb)
{
    Event e;

    while(rb_pop(rb, &e) == 0)
    {
        handle_event(e);
    }
}

int main(void)
{
    RingBuffer rb;
    rb_init(&rb);

    Event event_queue[9] = {0,1,2,3,4,0,1,2,2};

    for(int i = 0; i < 9; i++)
    {
        if(rb_push(&rb, event_queue[i]) != 0)
            printf("Queue Full\n");
    }

    process_events(&rb);
}