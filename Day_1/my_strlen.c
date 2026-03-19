#include "stdint.h"
#include "stdio.h"

size_t my_strlen(const char *s);

size_t my_strlen(const char *s)
{
    size_t count = 0;
    while(*s++)
        count++;

    return count;
}

int main(int argc, char *argv[])
{
    char str[10] = "Hello";
    uint8_t len = (uint8_t)(my_strlen(str));
    printf("Length is: %d", len);

    return 0;
}