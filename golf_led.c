/*******************************************************************
  file: golf_led.c
  author: Matěj Navrátil

  Definitions of functions working with LED data and mzapo board LEDs.
 *******************************************************************/
#include "golf_led.h"

extern unsigned char* mem_base;
mzapo_led_output game_led;

mzapo_led_output initLedData(){
    mzapo_led_output ret;
    ret.ledLine = getLedLineFromNum(0);
    ret.ledRGB1 = getLedRGBData(0x0,0x0,0x0);
    ret.ledRGB1 = getLedRGBData(0x0,0x0,0x0);
    return ret;
}

void setLedData(){
    mzapo_led_output param = game_led;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = param.ledLine;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = param.ledRGB1;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = param.ledRGB2;
}

void loadValueToLedRGB(int rgbLedNumber, uint32_t color){
    if(rgbLedNumber == BOTH_RGB_LEDS){
        game_led.ledRGB1 = color;
        game_led.ledRGB2 = color;
        return;
    }
    if(rgbLedNumber == RGB_LED_1){
        game_led.ledRGB1 = color;
        return;
    }
    if(rgbLedNumber == RGB_LED_2){
        game_led.ledRGB2 = color;
        return;
    }
}
