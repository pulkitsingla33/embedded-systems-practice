#include "button.h"

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