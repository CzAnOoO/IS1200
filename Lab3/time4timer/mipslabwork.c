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

  TRISD = TRISD & 0X0FE0;

  T2CON = 0x0;                 // Stop the timer and clear control register
  T2CONSET = 0X70;             // Set prescaler to 1:256
  PR2 = (80000000 / 256 / 10); // Set period for 100ms timeout

  TMR2 = 0X0;        // Clear timer register
  T2CONSET = 0x8000; // Start timer with ON bit

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{

  volatile int *porte = (volatile int *)0xbf886110;
  int sw = getsw();
  int btn = getbtns();

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

  // delay(1000);
  int timeroutcounter;
  if (IFS(0) & 0x100) // If timeout event flag is set
  {
    timeroutcounter++; // Increment timeout counter
    IFS(0) = 0x0;      // Clear the timeout event flag
  }

  if (timeroutcounter == 10)
  {
    *porte = *porte + 1;
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
    tick(&mytime);
    display_image(96, icon);
    timeroutcounter = 0;
  }
}
