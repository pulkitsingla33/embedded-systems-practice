#include <stdio.h>
#include <stdint.h>

#define NUM_COMMANDS 3

int parse_command(const char *cmd);

int parse_command(const char *cmd)
{
    if (cmd == NULL || *cmd == '\0')
        return -1;

    uint8_t flag = 0;

    const char *valid_commands[NUM_COMMANDS] = {"LED ON", "LED OFF", "STATUS"};

    for (int i = 0; i < NUM_COMMANDS; i++)
    {
        const char *s = valid_commands[i];
        const char *d = cmd;

        if(*d == '\0')
            return -1;

        while(*s && *d && (*s == *d))
        {
            s++;
            d++;

        }
        
        if(*s == '\0' && *d == '\0')
            return (i + 1);
    }

    return -1;
}

int main(int argc, char *argv[])
{
    char command[10] = "STATUS";

    printf("Command Return code: %d\n", parse_command(command));
}