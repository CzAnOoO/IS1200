#include <stdint.h>
#include <pic32mx.h>
/* -------------------------------------------------------------------------------- */
/*                                                                       by Zhengan */
/* -------------------------------------------------------------------------------- */
/*
TRIS = 1 --> Input
TRIS = 0 --> Output
*/
//Initializes IO 
void initIO()
{
    TRISDSET = 0xF00; //Switches 1-4
    TRISFSET = 0x2;   //BTN 1
    TRISDSET = 0xE0;  //BTNs 2-4
}
/*
Basic I/O Shield™ Reference Manual --> Uno32™ Board Reference Manual
chipKIT Pin#                       --> PIC32 Signal
SW (1-4) --> RD8-11
Pin (1-4) --> RF1, RD5-7
*/
uint8_t getsw(void)
{
    uint8_t sw = PORTD >> 8;
    return (sw &= 0xf);
}

uint8_t getbtns(void)
{

    uint8_t btns = PORTD >> 4;
    btns &= 0xE;    //btn 2-4
    uint8_t btn1 = PORTF >> 1;
    btn1 &= 0x1;    //btn 1
    return (btns |= btn1);
}

//returns switches and buttons
uint8_t getInputs()
{
    return (getsw() << 4) | getbtns();
}

/* -------------------------------------------------------------------------------- */