/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  volatile int *tris_E = (volatile int *)0xbf886100;

  // Set last 8 bits to zero, i.e. sets them as output pins.
  *tris_E = *tris_E & 0xff00;

  PORTD = PORTD & 0X0FE0;
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  volatile int *porte = (volatile int *)0xbf886110;
  *porte = *porte + 1;
  int sw = getsw();
  int btn = getbtns();
  /* Determine which button has been pressed 
  (use & instead of == can determine which buttons 
  have been pressed even when multiple buttons are pressed) */
  if (btn & 1)
  {
    mytime = (sw << 4) | (mytime & 0xff0f);
  }
  if (btn & 2)
  {
    mytime = (sw << 8) | (mytime & 0xf0ff);
  }
  if (btn & 4)
  {
    mytime = (sw << 12) | (mytime & 0x0fff);
  }
  delay(1000);
  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);
  display_image(96, icon);
}
