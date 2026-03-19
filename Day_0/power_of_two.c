#include "stdint.h"

int is_power_of_two(unsigned int x);


int is_power_of_two(unsigned int x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}