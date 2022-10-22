/*******************************************************************
  file: golf_lcd_print.h
  author: Matěj Navrátil

  Declarations of funcions loading characters, strings and numbers 
  in LCD buffers. There is also function for getting the width of
  printed string to allow text formating.
 *******************************************************************/
#ifndef GOLF_LCD_PRINT
#define GOLF_LCD_PRINT

#include "golf_global.h"
#include "golf_lcd.h"
#include "font_types.h"

#include <stdint.h>

/*Loads char c in specified font to "bufferType" buffer. Returns width of loaded char.*/
int putCharLCD(font_descriptor_t* font, char c, int x, int y, int size, uint16_t color, int bufferType);
/*Loads string c in specified font to "bufferType" buffer.*/
void printStringLCD(font_descriptor_t* font, char* c, int x, int y, int size, uint16_t color, int bufferType);
/*Loads number num in specified font to "bufferType" buffer.*/
void printNumberLCD(font_descriptor_t* font, int num, int x, int y, int size, uint16_t color, int bufferType);
/*Returns width of string c in specified font*/
int getStringFontLength(font_descriptor_t* font, char* c, int size);

#endif