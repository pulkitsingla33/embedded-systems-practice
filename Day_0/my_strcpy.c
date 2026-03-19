#include "stdint.h"
#include "stdio.h"

char *mystrcpy(char *dest, const char *src);


char *mystrcpy(char *dest, const char *src)
{
    char *ret = dest;

    // while(*src != '\0')
    //     *(dest++) = *(src++);

    while((*dest++ = *src++));

    

    return ret;
}

int main(int argc, char *argv[])
{
    char dest[10];
    char src[10] = "hello";
    mystrcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}