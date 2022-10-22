/*******************************************************************
  file: golf_global.h
  author: Matěj Navrátil

  Declarations of globally important program values like screen size,
  encoder max and min and gameplay values like golf ball start position
  and movement speeds.
 *******************************************************************/
#ifndef GOLF_SETTINGS
#define GOLF_SETTINGS

#include "golf_assets.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include "mzapo_parlcd.h"

#include <stdio.h>

//#define DEBUG //uncomment for debug messages
void DEBUG_SER_PRINT(char*, int);

/*****MZAPO*****/
#define LCD_WIDTH 480
#define LCD_HEIGHT 320	
#define GUI_HEIGHT 50	

/*On some boards 80, on some 96*/
#define KNOB_ONE_ROTATION 80
#define KNOB_DEF_MIN 0
#define KNOB_DEF_MAX 255

/*****Golf game*****/
/*Swing angle*/
/*On some boards 3.75f, on some 4.5f*/
#define GAME_RED_KNOB_MULT 4.5f
/*Swing power*/
/*On some boards 0.34375f, on some 0.4f*/
#define GAME_GREEN_KNOB_MULT 0.4125f
/*Zoom setings*/
#define GAME_BLUE_KNOB_MAX 40
#define GAME_BLUE_KNOB_MIN 0
/*Loading screen wait*/
#define LOADING_SCREEN_WAIT 30

/*Map rating*/
#define MAP1_PAR_RATING 3
#define MAP2_PAR_RATING 4
#define MAP3_PAR_RATING 5
/*Map starting ball position*/
#define MAP1_POSX 70
#define MAP1_POSY 270
#define MAP2_POSX 80
#define MAP2_POSY 260
#define MAP3_POSX 70
#define MAP3_POSY 270
/*Map hole flag position*/
#define MAP1_FLAGX 420
#define MAP1_FLAGY 43
#define MAP2_FLAGX 410
#define MAP2_FLAGY 253
#define MAP3_FLAGX 410
#define MAP3_FLAGY 253

/*Physic setings*/
#define TIME_INCREMENT 0.5f
#define DOWN_AC 5.0f
#define UP_V 16.0f
#define MAX_SWING_SPEED 16.0f
#define MAX_WIND_SPEED 8
#define BOUNCE_SAND 0.0f
#define BOUNCE_WATER 0.0f
#define BOUNCE_TALL_G 0.4f
#define BOUNCE_FIELD_G 0.8f
#define DRAG_WATER 1.0f
#define DRAG_SAND 1.0f
#define DRAG_TALL_G 0.8f
#define DRAG_FIELD_G 0.4f
#define DRAG_AIR 0.0f 
#define WIND_STRENGTH_CORRECTION 0.1f

#endif