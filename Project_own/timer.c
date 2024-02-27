#include <pic32mx.h>

void timerInit()
{
    /* Timer2 */
    T2CON = 0x0;           // Stop the timer and clear control register
    PR2 = (80000000 / 256 / 10); // Set period for 100ms timeout
    T2CONSET = 0X70;             // Set prescaler to 1:256
    IFSCLR(0) = 0x0100;          // Clear the timeout event flag 
    T2CONSET = 0x8000;           // Start timer with set ON bit to 1

    /* Timer3 */
    T3CON = 0x0;                 // Stop the timer and clear control register
    T3CONSET = 0X70;             // Set prescaler to 1:256
    PR2 = (80000000 / 256 / 1000); // Set period for 1ms timeout
    IFSCLR(0) = 0x1000;          // Clear the timeout event flag 
    T3CONSET = 0x8000;           // Start timer with set ON bit to 1

    /* Enabling interrupts */

    /* Timer2 */
    //IPCSET(2) = 0x19; // Priority 6, subpriority 1
    //IECSET(0) = 0x100;// Enable 
    
    // /* Timer3 */
    // IPCSET(3) = 0x19; // Priority 6, subpriority 1
    // IECSET(0) = 0x1000;// Enable 

    //enable_interrupt();

    return;
}
/* delay x deciseconds (ds) = 0.1 s */
void delayds(int x)
{
    TMR2 = 0x0;        // Clear timer register
    int count = 0;
    while (count < x)
    {
        if (IFS(0) & 0x100) // If timeout event flag is set
        {
            count++; // Increment timeout counter
            IFS(0) &= ~0x1000;      // Clear the timeout event flag
            //IFSCLR(0) = 0x0100;   // Clear the timeout event flag
        }
    }
    return;
}

/* delay x milliseconds (ms) = 0.1 s */
void delayms(int x)
{
    TMR3 = 0x0;        // Clear timer register
    int count = 0;
    while (count < x)
    {
        if (IFS(0) & 0x1000) // If timeout event flag is set
        {
            count++; // Increment timeout counter
            IFSCLR(0) = 0x01000;   // Clear the timeout event flag
        }
    }
    return;
}