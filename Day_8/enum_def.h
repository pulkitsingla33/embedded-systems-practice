#ifndef ENUM_DEF_H
#define ENUM_DEF_H

typedef enum
{
    IDLE,
    LED0,
    LED1,
    LED2,
    SPACE,
    LED_O,
    ON1,
    OFF1,
    OFF2,
    STAT0,
    STAT1,
    STAT2,
    STAT3,
    STAT4,
    STAT5
} UART_State;

typedef enum
{
    EVENT_NONE,
    EVENT_LED_ON,
    EVENT_LED_OFF,
    EVENT_STATUS,
    EVENT_BUTTON_PRESS,
    EVENT_TIMEOUT
} Event;

#endif