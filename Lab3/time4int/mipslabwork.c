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

int mytime = 0x0000;
int prime = 1234567;
char textstring[] = "text, more text, and even more text!";
int timeroutcounter = 0;
volatile int *port_E;

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0) & 0x100) // If timeout event flag is set
  {
    timeroutcounter++; // Increment timeout counter
    // IFS(0) = 0x0;      // Clear the timeout event flag
    IFSCLR(0) = 0x0100;   // Clear the timeout event flag
  }
  if (timeroutcounter == 10)
    {
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      timeroutcounter = 0;
    }
  /* Surprise assignment */
  if(IFS(0) & 0x80){
    //PORTE += 0x1; // Increment value in PORTE
    *port_E += 0x1; // Increment value in PORTE
    IFSCLR(0) = 0x80; // Clear INT1IF
  }
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  volatile int *tris_E = (volatile int *)0xbf886100;
  port_E = (volatile int *)0xbf886110;
  // Set last 8 bits to zero, i.e. sets them as output pins.
  *tris_E = *tris_E & 0xff00;
  *port_E = 0x0;    //clear porte

  TRISD = TRISD & 0X0FE0;

  T2CON = 0x0;                 // Stop the timer and clear control register
  T2CONSET = 0X70;             // Set prescaler to 1:256
  PR2 = (80000000 / 256 / 10); // Set period for 100ms timeout
  IFSCLR(0) = 0x0100;   // Clear the timeout event flag 
  TMR2 = 0X0;        // Clear timer register
  T2CONSET = 0x8000; // Start timer with set ON bit to 1

  /* Enabling interrupts */

  // Interrupt enable control. 
  // Set it to 1 to enable.
  // Enable interrupts from TMR2
  IPCSET(2) = 0x1A; // priority 6, subpriority 2
  IECSET(0) = 0x100;

  /* Surprise assignment */
  // Enable INT1
  IECSET(0) = 0x080;

  // Set priority for INT1
  // bit 28-26: 110 for priority 6
  // bit 25-24: 11 for sub-priority 1
  // IPCSET(1) = 0x19000000;
  volatile int *ipc1 = (volatile int*)0xbf8810a0;
  *ipc1 = 0x1b000000;
  enable_interrupt();

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}