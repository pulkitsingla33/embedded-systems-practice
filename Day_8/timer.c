#include "timer.h"

Event process_timer(int tick)
{
    if((tick != 0) && (tick % 5 == 0))
        return EVENT_TIMEOUT;

    return EVENT_NONE;
}