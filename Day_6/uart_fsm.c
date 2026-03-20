/*
Byte by Byte Finite State Machine (FSM) for UART Command Processing
Slight bug in code - for sequence LESTATUS\n, afer LE, STATUS is not detected
*/

#include <stdio.h>
#include <stdint.h>

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

int process_char(char c);

int process_char(char c)
{
    static UART_State current_state = IDLE;

    if((c == '\n') && ((current_state != ON1) && (current_state != OFF2) && (current_state != STAT5)))
        return -1;

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
                        return 1;
                break;

        case OFF1:  if(c == 'F')
                        current_state = OFF2;
                    else
                        current_state = IDLE;
                break;

        case OFF2:  current_state = IDLE;
                    if(c == '\n')
                        return 2;
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
                        return 3;
                break;
        
        default:    current_state = IDLE;   
    }

    return 0;
}


int main()
{
    char input[] = "LEDON\nLED OFF\nSTATUS\n";
    char *ptr = input;

    while(*ptr)
    {
        int result = process_char(*ptr);
        if(result == 1)
            printf("LED ON command received\n");
        else if(result == 2)
            printf("LED OFF command received\n");
        else if(result == 3)
            printf("STATUS command received\n");
        else if(result == -1)
            printf("Invalid command sequence\n");
        
        ptr++;
    }
    return 0;
}