/* -------------------------------------------------------------------------------- */
/* Based on code from lab files, modified by Zhengan                                */
/* -------------------------------------------------------------------------------- */
#include <stdint.h>
#include <pic32mx.h>
#include "timer.h"

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
void SPI2Init()
{	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
}

/* Power on sequence from basic I/O Shield Reference Manual:
Apply power to VDD
Send Display Off command
Initialize display to desired operating mode
Clear screen
Apply power to VBAT
Delay 100ms
Send Display On command */  
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}
void displayInit()
{
    COMMAND_MODE;
	quicksleep(10);	 //delayms(1);
	PORTFCLR = 0x40; //apply power to VDD and wait a while for the power
	quicksleep(1000000);	//delayms(10);
	
	SPI2send(0xAE);  //display OFF (sleep mode) 

    /* pull reset low then high */
    PORTGCLR = 0x200;  
	quicksleep(10);	//delayms(1); 
    PORTGSET = 0x200;
	quicksleep(10);	//delayms(1);

    SPI2send(0x8D);  //charge Pump Setting
    SPI2send(0x14);  //enable Charge Pump 

    SPI2send(0xD9);  //set Pre-charge Period
    SPI2send(0xF1);

    PORTFCLR = 0x20;      //apply power to VBAT
    quicksleep(10);	 //delayms(100);

    SPI2send(0xA1);  //column address 127 is mapped to SEG0
    SPI2send(0xC8);  //remapped mode. Scan from COM[N-1] to COM0

    SPI2send(0xDA);  //set COM Pins
    SPI2send(0x20);  //bit[4] Sequential COM pin configuration, bit[5]Enable COM Left/Right remap

    SPI2send(0xAF);  //display ON 

}
/* clear all data in buffer (set all byte to 0) */
void clearBuffer(uint8_t *buffer)
{
	int i;
	for (i = 0; i < GDDRAMSize; i++) *buffer++ = 0;
}

/* Add the bird image (any 8x8 pixel image) to display buffer and determine whether a collision occurs */
int drawBird2buffer(int x, int y, uint8_t *image , uint8_t *buffer)
{
	/* size off bird is 8x8 pixel */
	int startPage, endPage, endCol, offset, i;
	int flag = 0;	// Flag is used to record whether a collision occurs, 1 = collided 
	uint8_t *ptr = image;
	startPage = y / 8;
	endPage = (y + 7)/8;
	endCol = x + 8;
	if (endCol > 128) endCol = 128;
	if (endPage > 3) return 1;
	if (startPage == endPage)
	{
		for (i = x; i < endCol; i++)
		{
			flag = buffer[startPage * 128 + i] & *image;
			buffer[startPage * 128 + i] = *ptr++; 
		}
		return flag;
	}
	offset = (y % 8);	// number of bits needed to offset
	int temp = 0;
	for (i = x; i < endCol; i++)
		{			
			temp |= (*ptr++ << offset);
			//flag = buffer[startPage * 128 + i] & (0x00ff & temp);
			//flag = buffer[endPage * 128 + i] & ((0xff00 & temp) >> 8);
			buffer[startPage * 128 + i] = (0x00ff & temp);  
			buffer[endPage * 128 + i] = (0xff00 & temp) >> 8;
			temp = 0;
		}
	
	return flag;	
}

void displayUpdate(uint8_t *buffer)
{
	int i, j;
	for (i = 0; i < numPages; i++) {
		COMMAND_MODE;

		SPI2send(0x22); //Set Page Address
		SPI2send(i);    //Page start Address
		
		SPI2send(0x00); //Set the lower nibble (3:0) of the column start address
		SPI2send(0x10); //Set the higher nibble (7:4) of the column start address
		DATA_MODE;
		
		for (j = 0; j < numColumns; j++) {
			SPI2send(*buffer++);
		}
	}
}

void debug(int x, uint8_t *buffer, uint8_t *test)
{
	//int i;
	uint8_t *ptr = test;
	// for (i = 0; i < 8; i++)
	// {
	// 	buffer[x + i] = *ptr++;
	// }
	int startPage, endPage, endCol, offset, i;
	startPage = 0;
	if (1)
	{
		for (i = x; i < x + 8; i++)
		{
			//flag = buffer[startPage * 128 + i] & *image;
			buffer[startPage * 128 + i] = *ptr++; 
		}
		return ;
	}
	
}
/* -------------------------------------------------------------------------------- */
