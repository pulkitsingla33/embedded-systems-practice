#include <stdio.h>
#include <stdint.h>

int my_memcmp(const void *a, const void *b, size_t n);

int my_memcmp(const void *a, const void *b, size_t n)
{
    size_t i;
    // uint8_t varA, varB;
    const uint8_t *ptrA = a;
    const uint8_t *ptrB = b;


    while(n--)
    {
        // varA = *((uint8_t *)(a) + i);
        // varB = *((uint8_t *)(b) + i);

        // if(varA < varB)
        //     return -1;
        // else if(varA > varB)
        //     return 1;

        if(*ptrA != *ptrB)
            return (*ptrA - *ptrB);

        ptrA++;
        ptrB++;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    uint8_t a[3] = {1, 2, 6};
    uint8_t b[3] = {1, 2, 4};

    int cmp_val = my_memcmp(a, b, 3);

    printf("Compare Value: %d\n", cmp_val);

}