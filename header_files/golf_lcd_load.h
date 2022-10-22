/*******************************************************************
  file: golf_lcd_load.h
  author: Matěj Navrátil

  Declaration for functions loading images/shapes/textures into LCD 
  buffers. Background goes always to main buffer and ball to temporary 
  buffer the rest is controlable with bufferType.
 *******************************************************************/
#ifndef GOLF_LCD_LOAD
#define GOLF_LCD_LOAD

#include "golf_global.h"
#include "golf_lcd.h"

#include <stdint.h>

/*Loads chosen background to main LCD buffer. Background are defined in assets.*/
void loadBackgroundLCD(int backgroundImgID);
/*Loads chosen image to "bufferType" LCD buffer. Images are defined in assets*/
void loadImageLCD(int smallImgID, int x, int y, int size, int bufferType);
/*Loads specified rectangle to "bufferType" LCD buffer.*/
void loadRectLCD(int x1, int y1, int x2, int y2, int thick, uint16_t color, int bufferType);
/*Loads specified arrow to "bufferType" LCD buffer.*/
void loadArrowLCD(int x0, int y0, float x, float y, int length, int thick, bool fromMid, uint16_t color, int bufferType);
/*Loads ball to temporary LCD buffer. Returns pixel[x,y] from main buffer*/
uint16_t drawBall(int x, int y, int z);

#endif