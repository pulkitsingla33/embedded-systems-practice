#include <stdio.h>
#include <stdint.h>

/*
31          24 23      16 15      8 7      0
+--------------+--------+--------+--------+
| DEVICE_ID    | MODE   | SPEED  | ENABLE |
+--------------+--------+--------+--------+
*/

uint32_t make_config(uint8_t device_id, uint8_t mode, uint8_t speed, uint8_t enable);
uint32_t set_speed(uint32_t reg, uint8_t speed);
uint32_t toggle_enable(uint32_t reg);
int validate_config(uint32_t reg);

uint32_t make_config(uint8_t device_id, uint8_t mode, uint8_t speed, uint8_t enable)
{
    return ((uint32_t)((device_id << 24) | (mode << 16) | (speed << 8) | enable));
}

uint32_t set_speed(uint32_t reg, uint8_t speed)
{
    uint32_t mask = reg & 0xFFFF00FF;
    return (mask | (speed << 8));
}

uint32_t toggle_enable(uint32_t reg)
{
    uint8_t enable_toggled = ~(reg & 0x0FF);
    return ((reg & 0xFFFFFF00) | enable_toggled);
}

int validate_config(uint32_t reg)
{
    uint8_t mode = (reg >> 16) & 0xFF;
    uint8_t speed = (reg >> 8) & 0xFF;
    uint8_t enable = reg & 0xFF;

    if((mode <= 5) && ((speed & 0x01) == 0) && (enable > 0))
    {
        return 1; // Valid
    }
    return 0; // Invalid
}

int main(int argc, char *argv[])
{
    uint32_t config = make_config(0x12, 0x03, 0x04, 0x01);
    printf("Config: 0x%08X\n", config);

    config = set_speed(config, 0x06);
    printf("Updated Config: 0x%08X\n", config);

    config = toggle_enable(config);
    printf("Toggled Enable Config: 0x%08X\n", config);

    int is_valid = validate_config(config);
    printf("Is Config Valid? %s\n", is_valid ? "Yes" : "No");

    return 0;
}