#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdint.h>
#include "enum_def.h"

#define DEBOUNCE_THRESHOLD 3

Event process_button(int input);


#endif