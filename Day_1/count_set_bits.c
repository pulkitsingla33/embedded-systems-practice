#include <stdint.h>
#include <stdio.h>

int count_set_bits(uint32_t x);

int count_set_bits(uint32_t x)
{
    int count = 0;

    // while(x!=0)
    // {
    //     // if(x & 1)
    //     //     count++;

    //     count += (x&1);

    //     x = x >> 1;
    // }

    while(x)
    {
        x = x & (x-1);
        count++;
    }

    return count;
}

int main(int argc, char *argv[])
{
    uint32_t num_count = 10;
    int count = count_set_bits(num_count);

    printf("Set Bits: %d\n", count);

    return 0;
}