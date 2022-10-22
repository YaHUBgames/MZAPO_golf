/*******************************************************************
  file: golf_assets.h
  author: Matěj Navrátil

  Declarations of all images, textures, flowing textures, text constants 
  and colors for both LCD and RGB LEDs.
 *******************************************************************/
#ifndef GOLF_ASSETS
#define GOLF_ASSETS

#include "golf_imagebmp.h"

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define IMG_MAX_TIME 10
void img_timeFlowTick();
void img_timeFlowReset(int x);

union pixel{
	struct {
		unsigned b :5;
		unsigned g :6;
		unsigned r :5;
	};
	uint16_t rgb;
};
enum backgroundImages{
    img_default_background,
    img_tall_grass,
    img_field_grass,
    img_sand,
    img_water,
    img_loading_background,
    img_title_background,
    img_win_background,
    img_lose_background,
    img_pause_background,
    img_map1_background,
    img_map2_background,
    img_map3_background
};
enum smallImages{
    img_loading_dots,
    img_title_name,
    img_map_icon_1,
    img_map_icon_2,
    img_map_icon_3,
    img_hole_flag
};
typedef struct{
    int img_W;
    int img_H;
    int img_anim_T;
}_img_def;
_img_def initImgDef(int w,int h);
_img_def getImgDef(int img);
#define DO_NOT_ANIM -1

/*LCD colors*/
#define pixelRGB(r,g,b) b | (g << 5) | (r << 11)
#define P_BLACK 0x0000
#define P_TRANSP 0xffff
#define P_WHITE 0xfffe

#define P_GREEN1 (uint16_t)pixelRGB(0x00,0x3f,0x00)
#define P_GREEN2 (uint16_t)pixelRGB(0x00,0x3e,0x00)
#define P_GREEN3 (uint16_t)pixelRGB(0x00,0x3d,0x00)

#define P_GREEN4 (uint16_t)pixelRGB(0x00,0x1d,0x00)
#define P_GREEN5 (uint16_t)pixelRGB(0x00,0x1c,0x00)
#define P_GREEN6 (uint16_t)pixelRGB(0x00,0x0d,0x00)
#define P_YELLOW1 (uint16_t)pixelRGB(0x1f,0x3f,0x05)
#define P_YELLOW2 (uint16_t)pixelRGB(0x1f,0x3e,0x05)
#define P_BLUE1 (uint16_t)pixelRGB(0x00,0x00,0x1f)
#define P_BLUE2 (uint16_t)pixelRGB(0x00,0x00,0x1d)

#define P_RED1 (uint16_t)pixelRGB(0x1f,0x00,0x00)
#define P_RED2 (uint16_t)pixelRGB(0x1e,0x00,0x00)
#define P_RED3 (uint16_t)pixelRGB(0x1d,0x00,0x00)

/*RGB led colors*/
#define LED_D_GREEN 0x0000bb00
#define LED_L_GREEN 0x0000ff00
#define LED_WHITE 0x00ffffff
#define LED_BLUE 0x000000ff
#define LED_YELLOW 0x00ffef00
#define LED_RED 0x00ff0000
#define LED_BLACK 0x0

/*Textures*/
uint16_t tall_grass(int w,int h);
uint16_t field_border(int w,int h);
uint16_t field_grass(int w,int h);
uint16_t sand(int w,int h);
uint16_t water(int w,int h);
uint16_t red_field(int w,int h);

/*Map tools*/
#define PI 3.141592654f
#define toRad(deg) (deg*PI)/180
bool isInElipse(int w, int h, int x0, int y0, int A, int B, int alfa, int jitt);
bool isInCircle(int w, int h, int x0, int y0, int diam, int jitt);

/*Backgrounds*/
uint16_t default_background(int,int);
uint16_t loading_background(int,int);
uint16_t title_background(int,int);
uint16_t win_background(int,int);
uint16_t lose_background(int,int);
uint16_t pause_background(int,int);
uint16_t map1_background(int,int);
uint16_t map2_background(int,int);
uint16_t map3_background(int,int);

/*Images*/
uint16_t I_loading_dots(int,int);
uint16_t I_title_name(int,int);
uint16_t I_map_icon_1(int,int);
uint16_t I_map_icon_2(int,int);
uint16_t I_map_icon_3(int,int);
uint16_t I_hole_flag(int,int);

/*Scoring msg*/
typedef struct{
    char* name;
    int stokesThanPar;
}_score;   
extern const _score* SCORE_NAMES;

#endif