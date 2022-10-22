/*******************************************************************
  file: golf_lcd.c
  author: Matěj Navrátil

  Definitions functions working with LCD buffer data and working 
  with mzapo LCD.
 *******************************************************************/
#include "golf_lcd.h"

extern unsigned char* parlcd_mem_base;
mzapo_lcd_output game_lcd; 

mzapo_lcd_output initLcdData(){
    /*Alocate memmory for buffer*/
    union pixel* lcdData = (union pixel*)malloc(LCD_HEIGHT * LCD_WIDTH * sizeof(union pixel*));  //free is in OnLeave
    if(lcdData == NULL)
        exit(1);
    union pixel* tempData = (union pixel*)malloc(LCD_HEIGHT * LCD_WIDTH * sizeof(union pixel*));  //free is in OnLeave
    if(tempData == NULL)
        exit(1);
    union pixel* GUIData = (union pixel*)malloc(GUI_HEIGHT * LCD_WIDTH * sizeof(union pixel*));  //free is in OnLeave
    if(GUIData == NULL)
        exit(1);
    /*Set whole buffer on black/transparent */
    for (int h = 0; h < LCD_HEIGHT; h++)
        for (int w = 0; w < LCD_WIDTH; w++){
            lcdData[h * LCD_WIDTH + w].rgb = P_BLACK;
            tempData[h * LCD_WIDTH + w].rgb = P_TRANSP;
            if(h<GUI_HEIGHT)
                GUIData[h * LCD_WIDTH + w].rgb = P_TRANSP;
        }
    mzapo_lcd_output ret;
    ret.lcdBuffer = lcdData;
    ret.tempBuffer = tempData;
    ret.GUIbuffer = GUIData;
    ret.useGUI = false;
    return ret;
}

void resetTempBuffer(){
    for (int h = 0; h < LCD_HEIGHT; h++)
        for (int w = 0; w < LCD_WIDTH; w++){
            game_lcd.tempBuffer[h * LCD_WIDTH + w].rgb = P_TRANSP;
        }
}

void resetGUIBuffer(){
    for (int h = 0; h < GUI_HEIGHT; h++)
        for (int w = 0; w < LCD_WIDTH; w++){
            game_lcd.GUIbuffer[h * LCD_WIDTH + w].rgb = P_TRANSP;
        }
}

void setLCD(){
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int h = 0; h < LCD_HEIGHT; h++)
        for (int w = 0; w < LCD_WIDTH; w++){

            if(game_lcd.useGUI && h < GUI_HEIGHT && game_lcd.GUIbuffer[h * LCD_WIDTH + w].rgb != P_TRANSP)
                parlcd_write_data(parlcd_mem_base, game_lcd.GUIbuffer[h * LCD_WIDTH + w].rgb);
            else if(game_lcd.tempBuffer[h * LCD_WIDTH + w].rgb != P_TRANSP)
                parlcd_write_data(parlcd_mem_base, game_lcd.tempBuffer[h * LCD_WIDTH + w].rgb);
            else
                parlcd_write_data(parlcd_mem_base, game_lcd.lcdBuffer[h * LCD_WIDTH + w].rgb);
        }
}

void setToZoomBufferLCD(int zoom, int x0, int y0){
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    if(zoom == 0){
        setLCD();
        return;
    }

    for (int h = 0; h < LCD_HEIGHT; h++)
        for (int w = 0; w < LCD_WIDTH; w++)
        {
            int bufferZoomX = x0 - (int)(LCD_WIDTH/zoom/2) + w/zoom;
            int bufferZoomY = y0 - (int)(LCD_HEIGHT/zoom/2) + h/zoom;

            if(game_lcd.useGUI && h < GUI_HEIGHT && game_lcd.GUIbuffer[h * LCD_WIDTH + w].rgb != P_TRANSP)
                parlcd_write_data(parlcd_mem_base, game_lcd.GUIbuffer[h * LCD_WIDTH + w].rgb);
            else if(bufferZoomY >= 0 && bufferZoomY < LCD_HEIGHT && bufferZoomX >= 0 && bufferZoomX < LCD_WIDTH){

                if(game_lcd.tempBuffer[bufferZoomY * LCD_WIDTH + bufferZoomX].rgb != P_TRANSP)
                    parlcd_write_data(parlcd_mem_base, game_lcd.tempBuffer[bufferZoomY * LCD_WIDTH + bufferZoomX].rgb);
                else
                    parlcd_write_data(parlcd_mem_base, game_lcd.lcdBuffer[bufferZoomY * LCD_WIDTH + bufferZoomX].rgb);
            }
            else
                parlcd_write_data(parlcd_mem_base, water(w,h));
        }
}
