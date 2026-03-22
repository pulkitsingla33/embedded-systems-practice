#include "event.h"

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