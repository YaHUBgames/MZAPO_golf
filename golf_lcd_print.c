/*******************************************************************
  file: golf_lcd_print.c
  author: Matěj Navrátil

  Defines functions that load char, string or number to LCD screen
  buffers. In all functions you can chose font and buffer type.
 *******************************************************************/
#include "golf_lcd_print.h"

extern mzapo_lcd_output game_lcd;

int putCharLCD(font_descriptor_t* font, char c, int x, int y, int size, uint16_t color, int bufferType){   
    for (int w = 0; w < font->maxwidth*size; w++)
        for (int h = 0; h < font->height*size; h++){
            if(y+h >= LCD_HEIGHT || x+w >= LCD_WIDTH)
                return 0; 
            if(font->bits[ (c - font->firstchar) * font->height + (h/size)] & (1 << (16 - (w/size)))){
                switch (bufferType)
                {
                case BUFFER_MAIN:
                    game_lcd.lcdBuffer[(y + h)*LCD_WIDTH + (x + w)].rgb = color;
                    break;
                case BUFFER_TEMP:
                    game_lcd.tempBuffer[(y + h)*LCD_WIDTH + (x + w)].rgb = color;
                    break;
                case BUFFER_GUI:
                    if(y + h < GUI_HEIGHT)
                        game_lcd.GUIbuffer[(y + h)*LCD_WIDTH + (x + w)].rgb = color;
                    break;
                
                default:
                    break;
                }
            }
        }

    if(font->width != 0)
        return size * font->width[(c - font->firstchar)];
    return size * font->maxwidth;
}

void printStringLCD(font_descriptor_t* font, char* c, int x, int y, int size, uint16_t color, int bufferType){
    int i = 0;
    int widthAdd = 0;
    while (c[i] != '\0'){
        widthAdd += putCharLCD(font, c[i], x + widthAdd, y, size, color, bufferType);
        i++;
    }
    DEBUG_SER_PRINT("Width of printed string is", widthAdd);
}

void printNumberLCD(font_descriptor_t* font, int num, int x, int y, int size, uint16_t color, int bufferType){
    int i = 1;
    while (i<=num)
        i*=10;
    
    int widthAdd = 0;
    while (i>1)
    {
        i/=10;
        widthAdd += putCharLCD(font, num/i + '0', x + widthAdd, y, size, color, bufferType);
        num-=(int)(num/i) * i;
    }
    DEBUG_SER_PRINT("Width of printed number is", widthAdd);
}

int getStringFontLength(font_descriptor_t* font, char* c, int size){
    int i = 0;
    int widthAdd = 0;
    while (c[i] != '\0')
    {
        if(font->width != 0)
            widthAdd +=  size * font->width[( c[i] )- font->firstchar];
        else
            widthAdd +=  size * font->maxwidth;
        i++;
    }
    DEBUG_SER_PRINT("Width of string is ", widthAdd);
    return widthAdd;
}
