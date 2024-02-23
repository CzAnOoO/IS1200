#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void)
{

    int sw = PORTD >> 8;
    return (sw = sw & 0X000f);
}

int getbtns(void)
{
    int btn = PORTD >> 5;
    return btn = (btn & 0X0007);
}
