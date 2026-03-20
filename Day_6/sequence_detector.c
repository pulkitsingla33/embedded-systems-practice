#include <stdio.h>
#include <stdint.h>

typedef enum
{
    S0, //Reset
    S1, //1
    S2, //10
    S3 //101
} FSM_State;

int detect_sequence(int bit);

int detect_sequence(int bit)
{
    static FSM_State current_state = S0;

    switch(current_state)
    {
        case S0:    if(bit == 1)
                        current_state = S1;
                    else
                        current_state = S0;
                break;

        case S1:    if(bit == 1)
                        current_state = S1;
                    else
                        current_state = S2;
                break;

        case S2:    if(bit == 1)
                        current_state = S3;
                    else
                        current_state = S0;
                break;
                
        case S3:    if(bit == 1)
                    {
                        current_state = S1;
                        return 1;
                    }
                    else
                        current_state = S2;
                break;

        default:    current_state = S0;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int sequence_byte[12] = {1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0};

    for(int i = 0; i<12; i++)
        printf("Input:%d, Output: %d\n", sequence_byte[i], detect_sequence(sequence_byte[i]));
    
    return 0;
}