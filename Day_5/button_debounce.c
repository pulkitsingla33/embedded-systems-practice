#include <stdio.h>
#include <stdint.h>

#define DEBOUNCE_THRESHOLD 3

int debounce(int input);

int debounce(int input)
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
            return 1;
        }
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    return 0;
}