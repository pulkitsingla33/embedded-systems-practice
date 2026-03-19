#include <stdio.h>
#include <stdint.h>

char *my_strchr(const char *s, int c);

char *my_strchr(const char *s, int c)
{
    while(*s)
    {
        if(*s == (char)c)
            return (char *)s;
        s++;
    }

    if((char)c == '\0')
        return (char *)s;

    return NULL;
}

int main(int argc, char *argv[])
{
    char buffer[10] = "hello";    
    char *ptr = my_strchr(buffer, '\0');
    printf("%p\n", (void *)ptr);

    return 0;
}