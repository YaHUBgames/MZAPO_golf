/*******************************************************************
  file: golf_led.h
  author: Matěj Navrátil

  Declaration of structure holding all information about LEDs and all
  functions working with this data and mzapo board LEDs.
 *******************************************************************/
#ifndef GOLF_LED
#define GOLF_LED

#include "golf_global.h"

#include <stdint.h>

typedef struct{
    uint32_t ledLine;
    uint32_t ledRGB1;
    uint32_t ledRGB2;
}mzapo_led_output;

mzapo_led_output initLedData();
enum load_RGB_led_type{BOTH_RGB_LEDS,RGB_LED_1,RGB_LED_2};
void loadValueToLedRGB(int rgbLedNumber, uint32_t color);
/*Apply loaded values to all LEDs on mzapo*/
void setLedData();

#define getLedLineFromNum(x) x!=0 ? (uint32_t)(0x0ffffffff >> (33-(x))) : 0x0
#define getLedRGBData(r,g,b) b + (g << 8) + (r << 16)

#endif