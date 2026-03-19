#include <stdio.h>
#include <stdint.h>

void *my_memmove(void *dest, const void *src, size_t n);

void *my_memmove(void *dest, const void *src, size_t n)
{
    uint8_t *d = dest;
    const uint8_t *s = src;

    if (d < s)
    {
        while(n--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        d += n;
        s += n;
        while(n--)
        
            *--d = *--s;
    
    }

    return dest;
}


int main(int argc, char *argv[])
{
    uint8_t src[8] = {1,2,3,4,5,0,0,0};

    my_memmove(src + 2, src, 5);

    for(int i = 0; i<8; i++)
    {
        printf("Location:%d, Value:%d\n", i, src[i]);
    }
}

