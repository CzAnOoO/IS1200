/* -------------------------------------------------------------------------------- */
/* Based on code from lab files, modified by Zhengan                                */
/* -------------------------------------------------------------------------------- */
#include <stdint.h>
#include <pic32mx.h>

#define numColumns 128 // COL
#define numPages 4     // PAGE
#define GDDRAMSize numColumns*numPages

#define COMMAND_MODE (PORTFCLR = 0x10)
#define DATA_MODE (PORTFSET = 0x10)


uint8_t SPI2send(uint8_t data) 
{
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}
 
/* Power on sequence from basic I/O Shield Reference Manual:
Apply power to VDD
Send Display Off command
Initialize display to desired operating mode
Clear screen
Apply power to VBAT
Delay 100ms
Send Display On command */  

void displayInit()
{
    COMMAND_MODE;
	
	PORTFCLR = 0x40; //apply power to VDD VDD and wait a while for the power
	delay(10);
	
	SPI2send(0xAE);  //display OFF (sleep mode) 

    /* pull reset low then high */
    PORTGCLR = 0x200;     
    delay(10);
    PORTGSET = 0x200;
 

    SPI2send(0x8D);  //charge Pump Setting
    SPI2send(0x14);  //enable Charge Pump 

    SPI2send(0xD9);  //set Pre-charge Period
    SPI2send(0xF1);

    PORTFCLR = 0x40;      //apply power to VBAT
    quicksleep(10000000);

    SPI2send(0xA1);  //column address 127 is mapped to SEG0
    SPI2send(0xC8);  //remapped mode. Scan from COM[N-1] to COM0

    SPI2send(0xDA);  //set COM Pins
    SPI2send(0x20);  //bit[4] Sequential COM pin configuration, bit[5]Enable COM Left/Right remap

    SPI2send(0xAF);  //display ON 

}

void displayUpdate(uint8_t *Buffer)
{
	int i;
	
	for (i = 0; i < numPages; i++) {
		COMMAND_MODE;

		SPI2send(0x22); //Set Page Address
		SPI2send(i);    //Page start Address
		
		SPI2send(0x00); //Set the lower nibble (3:0) of the column start address
		SPI2send(0x10); //Set the higher nibble (7:4) of the column start address
		DATA_MODE;
		
		/* Haven't decided yet which way to refresh the display */

	}
}
/* -------------------------------------------------------------------------------- */
