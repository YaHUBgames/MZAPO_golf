/*******************************************************************
  file: golf_lcd.h
  author: Matěj Navrátil

  Declarations of structure holding all LCD image buffer information,
  functions working with this data and working with mzapo LCD.
 *******************************************************************/
#ifndef GOLF_LCD
#define GOLF_LCD

#include "golf_global.h"

#include <stdbool.h>

typedef struct{
    union pixel *lcdBuffer;
    union pixel *tempBuffer;
    union pixel *GUIbuffer;
    bool useGUI;
}mzapo_lcd_output;
mzapo_lcd_output initLcdData();
enum buffer_type{BUFFER_MAIN,BUFFER_TEMP,BUFFER_GUI};
void resetTempBuffer();
void resetGUIBuffer();

/*Sets buffers to LCD screen. In order GUI-Temp-Main*/
void setLCD();
/*Sets buffers to LCD screen. In order GUI-ZOOMED(Temp)-ZOOMED(Main)*/
void setToZoomBufferLCD(int zoom, int x0, int y0);

#endif