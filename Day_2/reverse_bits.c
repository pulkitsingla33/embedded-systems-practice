#include <stdio.h>
#include <stdint.h>

uint8_t reverse_bits(uint8_t x);

uint8_t reverse_bits(uint8_t x)
{
    uint8_t rev_val = 0;
    for(int i = 0; i < 8; i++)
    {
        rev_val = (rev_val << 1) | (x & 0x1);
        x >>= 1;
    }

    //Alternative Approach:
    /*
    x = (x & 0xF0) >> 4 | (x & 0x0F) << 4;
    x = (x & 0xCC) >> 2 | (x & 0x33) << 2;
    x = (x & 0xAA) >> 1 | (x & 0x55) << 1;
    rev_val = x;
    */

    return rev_val;
}

int main(int argc, char *argv[])
{
    uint8_t current_num = 3;
    uint8_t reversed = reverse_bits(current_num);

    printf("Reversed: %d\n", reversed);
    
    return 0;
}