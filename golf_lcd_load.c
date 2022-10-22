/*******************************************************************
  file: golf_lcd_load.c
  author: Matěj Navrátil

  Definitions for loading images,shapes and textures to LCD buffers.
  Images and background are defined in golf_assets files.
 *******************************************************************/
#include "golf_lcd_load.h"

extern mzapo_lcd_output game_lcd;

void loadBackgroundLCD(int backgroundImgID){
	uint16_t ret = P_BLACK;
    
    for (int h = 0; h < LCD_HEIGHT; h++){
        for (int w = 0; w < LCD_WIDTH; w++){
			switch (backgroundImgID)
			{
                case img_loading_background:
					ret = loading_background(w, h);
					break;
                case img_title_background:
					ret = title_background(w, h);
					break;
                case img_lose_background:
					ret = lose_background(w, h);
					break;
                case img_win_background:
					ret = win_background(w, h);
					break;
                case img_pause_background:
					ret = pause_background(w, h);
					break;
                case img_map1_background:
					ret = map1_background(w, h); 
					break;
                case img_map2_background:
					ret = map2_background(w, h); 
					break;
                case img_map3_background:
					ret = map3_background(w, h); 
					break;
				default:
					ret = default_background(w, h);
					break;
			}
            game_lcd.lcdBuffer[h * LCD_WIDTH + w].rgb = ret;
		}
	}
}

void loadImageLCD(int smallImgID, int x, int y, int size, int bufferType){
    _img_def img = getImgDef(smallImgID);
	uint16_t ret = P_BLACK;
    for (int h = 0; h < img.img_H * size; h++){
        for (int w = 0; w < img.img_W * size; w++)
        {
            switch (smallImgID)
            {
            case img_loading_dots:
                ret = I_loading_dots(w / size,h / size);
                break;
            case img_title_name:
                ret = I_title_name(w / size, h / size);
                break;
            case img_map_icon_1:
                ret = I_map_icon_1(w / size, h / size);
                break;
            case img_map_icon_2:
                ret = I_map_icon_2(w / size, h / size);
                break;
            case img_map_icon_3:
                ret = I_map_icon_3(w / size, h / size);
                break;
            case img_hole_flag:
                ret = I_hole_flag(w / size, h / size);
                break;
            default:
                ret = P_TRANSP;
                break;
            }
            if(ret != P_TRANSP){
                switch (bufferType)
                {
                case BUFFER_MAIN: 
                    game_lcd.lcdBuffer[(h+y) * LCD_WIDTH + (w+x)].rgb = ret;
                    break;
                case BUFFER_TEMP:
                    game_lcd.tempBuffer[(h+y) * LCD_WIDTH + (w+x)].rgb = ret;
                    break;
                case BUFFER_GUI:
                    if(h < GUI_HEIGHT)
                        game_lcd.tempBuffer[(h+y) * LCD_WIDTH + (w+x)].rgb = ret;
                    break;
                
                default:
                    break;
                }
            }
        }
    }
    if(img.img_anim_T != DO_NOT_ANIM)
        img_timeFlowTick();
}

void loadRectLCD(int x1, int y1, int x2, int y2, int thick, uint16_t color, int bufferType){
    int temp;
    if(x1 > x2){
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if(y1 > y2){
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    /*Vertical lines*/
    for (int h = y1; h < y2; h++){
        for (int t = 0; t < thick; t++){
            switch (bufferType)
            {
            case BUFFER_MAIN: 
                game_lcd.lcdBuffer[(h) * LCD_WIDTH + (x1+t)].rgb = color;
                game_lcd.lcdBuffer[(h) * LCD_WIDTH + (x2-t)].rgb = color;
                break;
            case BUFFER_TEMP:
                game_lcd.tempBuffer[(h) * LCD_WIDTH + (x1+t)].rgb = color;
                game_lcd.tempBuffer[(h) * LCD_WIDTH + (x2-t)].rgb = color;
                break;
            case BUFFER_GUI:
                if(h < GUI_HEIGHT){
                    game_lcd.GUIbuffer[(h) * LCD_WIDTH + (x1+t)].rgb = color;
                    game_lcd.GUIbuffer[(h) * LCD_WIDTH + (x2-t)].rgb = color;
                }
                break;
            default:
                break;
            }
        }
    }
    /*Horizontal lines*/
    for (int w = x1; w < x2; w++){
        for (int t = 0; t < thick; t++){
            switch (bufferType)
            {
            case BUFFER_MAIN:
                game_lcd.lcdBuffer[(y1+t) * LCD_WIDTH + (w)].rgb = color;
                game_lcd.lcdBuffer[(y2-t) * LCD_WIDTH + (w)].rgb = color;
                break;
            case BUFFER_TEMP:
                game_lcd.tempBuffer[(y1+t) * LCD_WIDTH + (w)].rgb = color;
                game_lcd.tempBuffer[(y2-t) * LCD_WIDTH + (w)].rgb = color;
                break;
            case BUFFER_GUI:
                if((y1+t) < GUI_HEIGHT)
                game_lcd.GUIbuffer[(y1+t) * LCD_WIDTH + (w)].rgb = color;
                game_lcd.GUIbuffer[(y2-t) * LCD_WIDTH + (w)].rgb = color;
                break;
            default:
                break;
            }
        }   
    }
}

void loadArrowLCD(int x0, int y0, float x, float y, int length, int thick, bool fromMid, uint16_t color, int bufferType){
    float posX = x0+1;
    float posY = y0+1;
    if(fromMid){
        for (int i = 0; i < length/2; i++){
            posX-=x;
            posY-=y;
        }
    }

    /*Arrow line*/
    for (int i = 0; i < length; i++){
        for (int h = posY-thick; h < posY+thick; h++)
            for (int w = posX-thick; w < posX+thick; w++){
                if(h < LCD_HEIGHT && h >= 0 && w < LCD_WIDTH && w >= 0){
                    switch (bufferType)
                    {
                    case BUFFER_MAIN:
                        game_lcd.lcdBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_TEMP:
                        game_lcd.tempBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_GUI:
                        if(h < GUI_HEIGHT)
                            game_lcd.GUIbuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        posX+=x;
        posY+=y;
    }
    
    x0 = posX;
    y0 = posY;
    float xR = x * (-0.7f) + y * (-0.7f);
    float YR = x * (0.7f) + y * (-0.7f);

    /*One side of the arrow head*/
    for (int i = 0; i < length/3; i++){
        for (int h = posY-thick; h < posY+thick; h++)
            for (int w = posX-thick; w < posX+thick; w++){
                if(h < LCD_HEIGHT && h >= 0 && w < LCD_WIDTH && w >= 0){
                    switch (bufferType)
                    {
                    case BUFFER_MAIN:
                        game_lcd.lcdBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_TEMP:
                        game_lcd.tempBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_GUI:
                        if(h < GUI_HEIGHT)
                            game_lcd.GUIbuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        posX+=xR;
        posY+=YR;
    }
    posX = x0;
    posY = y0;
    float xL = x * (-0.7f) + y * (0.7f);
    float yL = x * (-0.7f) + y * (-0.7f);

    /*Other side of the arrow head*/
    for (int i = 0; i < length/3; i++){
        for (int h = posY-thick; h < posY+thick; h++)
            for (int w = posX-thick; w < posX+thick; w++){
                if(h < LCD_HEIGHT && h >= 0 && w < LCD_WIDTH && w >= 0){
                    switch (bufferType)
                    {
                    case BUFFER_MAIN:
                        game_lcd.lcdBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_TEMP:
                        game_lcd.tempBuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    case BUFFER_GUI:
                        if(h < GUI_HEIGHT)
                            game_lcd.GUIbuffer[(h) * LCD_WIDTH + (w)].rgb = color;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        posX+=xL;
        posY+=yL;
    }
}

uint16_t drawBall(int x, int y, int z){
    int size = 1;
    for (int h = y-z-size; h <= y+z+size; h++)
        for (int w = x-z-size; w <= x+z+size; w++)
        {
            if(h< LCD_HEIGHT && h >= 0 && w < LCD_WIDTH && w >=0)
            {
                if( (x-w)*(x-w) + (y-h)*(y-h) <= (size+z)*(size+z))
                    game_lcd.tempBuffer[(h)*LCD_WIDTH + (w)].rgb = P_WHITE;
            }
        }
    if(y< LCD_HEIGHT && y >= 0 && x < LCD_WIDTH && x >=0)
        return game_lcd.lcdBuffer[y*LCD_WIDTH + x].rgb;
    return P_TRANSP;
}