#include <stdio.h>
#include <stdint.h>

int lowest_set_bit(uint32_t x);

int lowest_set_bit(uint32_t x)
{
    //Return lowest set bit position in x. If x is 0, return -1.
    if(x == 0)
        return -1;
    
    int pos = 0;
    int mask = x & -x; //Isolate lowest set bit
    while(mask > 1)
    {
        mask >>= 1;
        pos++;
    }

    return pos;
}

int main(int argc, char *argv[])
{
    uint32_t num = 8; //Binary: 10010
    int lsb_pos = lowest_set_bit(num);

    printf("Lowest Set Bit Position: %d\n", lsb_pos);
    
    return 0;
}