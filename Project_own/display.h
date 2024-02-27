#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>

void SPI2Init();
uint8_t SPI2send(uint8_t data);
void displayInit();
void clearBuffer(uint8_t *Buffer);
void displayUpdate(uint8_t *Buffer);
int drawBird2buffer(int x, int y, uint8_t *image , uint8_t *buffer);

void debug(int x, uint8_t *Buffer, uint8_t *test);

#endif