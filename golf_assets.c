/*******************************************************************
  file: golf_assets.c
  author: Matěj Navrátil

  Definitions of all images, textures, flowing textures and text 
  constants. Possible animations for some images and textures. 
  Jitt global variable used for un-even map field border.
 *******************************************************************/
#include "golf_assets.h"

int animTime = 0;
int animFrame = 0;
void img_timeFlowTick(){
	animTime ++;
	if(animTime >= animFrame)
		animTime = 0;
}
void img_timeFlowReset(int x){
	animTime = 0;
	animFrame = x;
}

/*Textures*/
uint16_t tall_grass(int w,int h){
	uint16_t ret = P_GREEN5;
	if(h % 20 < 10)
		ret = P_GREEN4;
	return ret;
}
uint16_t field_border(int w,int h){
	uint16_t ret = P_GREEN6;
	return ret;
}
uint16_t field_grass(int w,int h){
	uint16_t ret = P_GREEN1;
	if(h % 20 < 10)
	{
		if(w % 20 < 10)
			ret = P_GREEN3;
		else
			ret = P_GREEN2;
	}
	else
		if(w % 20 < 10)
			ret = P_GREEN2;
		
	return ret;
}
uint16_t sand(int w,int h){
	uint16_t ret = P_YELLOW1;
	if(w % 20 < 10)
		ret = P_YELLOW2;
	return ret;
}
uint16_t water(int w,int h){
	uint16_t ret = P_BLUE1;
	if(h % 20 < 10)
		ret = P_BLUE2;
	return ret;
}
uint16_t red_field(int w,int h){
	uint16_t ret = P_RED1;
	if(h % 20 < 10)
	{
		if(w % 20 < 10)
			ret = P_RED3;
		else
			ret = P_RED2;
	}
	else
		if(w % 20 < 10)
			ret = P_RED2;
		
	return ret;
}

/*Map tools*/
bool isInCircle(int w, int h, int x0, int y0, int diam, int jitt){
	x0 = w - x0 - jitt;
	y0 = h - y0 - jitt;
	if( (x0)*(x0) + (y0)*(y0) <= diam*diam)
		return true;
	return false;
}
bool isInElipse(int w, int h, int x0, int y0, int A, int B, int alfa, int jitt){
	A -= jitt;
	B -= jitt;
	float fi = toRad(alfa);
	if( (pow(sin(fi),2)*(A*A*pow(w-x0,2)+B*B*pow(h-y0,2)) + pow(cos(fi),2)*(B*B*pow(w-x0,2)+A*A*pow(h-y0,2)) + 2*sin(fi)*cos(fi)*(B*B-A*A)*(w-x0)*(h-y0)) < A*A*B*B )
		return true;
	return false;
}
/*Backgrounds*/
uint16_t default_background(int w,int h){
	uint16_t ret = P_WHITE;
	return ret;
}
uint16_t loading_background(int w,int h){
	uint16_t ret = P_BLACK;
	return ret;
}
uint16_t title_background(int w,int h){
	uint16_t ret = field_grass(w + animTime, h + animTime);
	return ret;
}
uint16_t win_background(int w,int h){
	uint16_t ret = field_grass(w + animTime, h + animTime);
	return ret;
}
uint16_t lose_background(int w,int h){
	uint16_t ret = red_field(w + animTime, h + animTime);
	return ret;
}
uint16_t pause_background(int w,int h){
	uint16_t ret = tall_grass(w + animTime, h + animTime);;
	return ret;
}

int jitt = 0;
uint16_t map1_background(int w,int h){
	uint16_t ret = tall_grass(w,h);

	if( isInCircle(w, h, 80, 250, 65, jitt) )
		ret = field_border(w, h);
	else if( isInCircle(w, h, 400, 70, 65, jitt) )
		ret = field_border(w, h);
	else if( isInElipse(w, h, 240, 160, 220, 120, 150, jitt) )
		ret = field_border(w, h);

	if( isInCircle(w, h, 80, 250, 50, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 400, 70, 50, jitt) )
		ret = field_grass(w, h);
	else if( isInElipse(w, h, 240, 160, 200, 100, 150, jitt) )
		ret = field_grass(w, h);

	if( isInElipse(w, h, 130, 110, 100, 65, 140, jitt) )
		ret = sand(w, h);
	else if( isInElipse(w, h, 300, 250, 50, 80, 118, jitt) )
		ret = water(w, h);

	if( isInCircle(w, h, 420, 60, 3, 0) )
		ret = P_BLACK;

	jitt++;
	if(jitt>10)
		jitt = rand()%5;

	return ret;
}
uint16_t map2_background(int w,int h){
	uint16_t ret = tall_grass(w,h);

	if( isInCircle(w, h, 80, 250, 40, jitt) )
		ret = field_border(w, h);
	else if( isInCircle(w, h, 400, 250, 40, jitt) )
		ret = field_border(w, h);
	else if( isInCircle(w, h, 240, 70, 60, jitt) )
		ret = field_border(w, h);
	else if( isInElipse(w, h, 160, 160, 180, 60, -50, jitt) )
		ret = field_border(w, h);
	else if( isInElipse(w, h, 325, 160, 180, 60, 50, jitt) )
		ret = field_border(w, h);

	if( isInCircle(w, h, 80, 250, 25, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 400, 250, 30, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 240, 70, 45, jitt) )
		ret = field_grass(w, h);
	else if( isInElipse(w, h, 160, 160, 160, 40, -50, jitt) )
		ret = field_grass(w, h);
	else if( isInElipse(w, h, 325, 160, 160, 40, 50, jitt) )
		ret = field_grass(w, h);
	

	if( isInElipse(w, h, 130, 120, 60, 40, 150, jitt) )
		ret = sand(w, h);
	else if( isInElipse(w, h, 390, 160, 50, 40, 20, jitt) )
		ret = sand(w, h);
	else if( isInElipse(w, h, 280, 40, 60, 40, 20, jitt) )
		ret = sand(w, h);
	else if( isInElipse(w, h, 245, 250, 120, 90, 20, jitt) )
		ret = water(w, h);
	
	if( isInElipse(w, h, 245, 250, 20, 30, 20, jitt) )
		ret = field_grass(w, h);

	if( isInCircle(w, h, 410, 270, 3, 0) )
		ret = P_BLACK;

	jitt++;
	if(jitt>10)
		jitt = rand()%5;

	return ret;
}
uint16_t map3_background(int w,int h)
{
	uint16_t ret = water(w,h);

	if( isInCircle(w, h, 65, 265, 45, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 405, 265, 45, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 65, 55, 45, jitt) )
		ret = field_grass(w, h);

	if( isInCircle(w, h, 75, 188, 25, jitt) )
		ret = sand(w, h);
	else if( isInCircle(w, h, 130, 140, 35, jitt) )
		ret = sand(w, h);
	else if( isInCircle(w, h, 185, 85, 25, jitt) )
		ret = sand(w, h);
	else if( isInCircle(w, h, 280, 80, 35, jitt) )
		ret = sand(w, h);
	else if( isInCircle(w, h, 380, 100, 25, jitt) )
		ret = sand(w, h);
	else if( isInCircle(w, h, 410, 170, 35, jitt) )
		ret = sand(w, h);

	if( isInCircle(w, h, 180, 220, 25, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 320, 220, 25, jitt) )
		ret = field_grass(w, h);
	else if( isInCircle(w, h, 260, 180, 35, jitt) )
		ret = field_grass(w, h);

	if( isInCircle(w, h, 410, 270, 3, 0) )
		ret = P_BLACK;

	jitt++;
	if(jitt>10)
		jitt = rand()%5;

	return ret;
}


/*Images*/
_img_def initImgDef(int w, int h)
{
	_img_def ret;
	ret.img_W = w;
	ret.img_H = h;
	ret.img_anim_T = 0;
	return ret;
}
/*Images definitions*/
static _img_def i_loading_dots = {50, 10, 10};
uint16_t I_loading_dots(int w,int h)
{
	uint16_t ret = P_BLACK;
	if(w >= 50 || w < 0 || h >= 10 || h < 0)
		return ret;
	if( (w + animTime*2)%20 >= 0 && (w + animTime*2 + 10)%20 < 10)
		ret = P_WHITE;
	return ret;
}
static _img_def i_title_name = {76, 45, DO_NOT_ANIM};
uint16_t I_title_name(int w,int h)
{
	uint16_t ret = IMG_TITLE[w + h*i_title_name.img_W];
	return ret;
}
static _img_def i_map_icon_1 = {20, 20, DO_NOT_ANIM};
uint16_t I_map_icon_1(int w,int h)
{
	uint16_t ret = IMG_MAPICON1[w + h*i_map_icon_1.img_W];
	return ret;
}
static _img_def i_map_icon_2 = {20, 20, DO_NOT_ANIM};
uint16_t I_map_icon_2(int w,int h)
{
	uint16_t ret = IMG_MAPICON2[w + h*i_map_icon_2.img_W];
	return ret;
}
static _img_def i_map_icon_3 = {20, 20, DO_NOT_ANIM};
uint16_t I_map_icon_3(int w,int h)
{
	uint16_t ret = IMG_MAPICON3[w + h*i_map_icon_3.img_W];
	return ret;
}
static _img_def i_hole_flag = {10, 17, DO_NOT_ANIM};
uint16_t I_hole_flag(int w,int h)
{
	uint16_t ret = IMG_HOLEFLAG[w + h*i_hole_flag.img_W];
	return ret;
}
/*Images*/
_img_def getImgDef(int img)
{
	switch (img)
	{
	case img_loading_dots:
		return i_loading_dots;
	case img_title_name:
		return i_title_name;
	case img_map_icon_1:
		return i_map_icon_1;
	case img_map_icon_2:
		return i_map_icon_2;
	case img_map_icon_3:
		return i_map_icon_3;
	case img_hole_flag:
		return i_hole_flag;
	default:
		break;
	}
	return initImgDef(0,0);
}

/*Scoring msg*/
const _score _SCORE_NAME[] =	{ {"Water ball",-10},{"Hole-in-one",-5},{"Condor",-4},{"Albatross",-3},{"Eagle",-2},{"Birdie",-1},{"Par",0},
{"Bogey",1},{"Double Bogey",2},{"Triple Bogey",3},{"Quadruple Bogey",4},{"A lot over par",5} };
const _score* SCORE_NAMES = _SCORE_NAME;