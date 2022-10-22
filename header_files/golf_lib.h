/*******************************************************************
  file: golf_lib.h
  author: Matěj Navrátil

  Declarations of all state structures and enumerators for scene state,
  game state, mapID and ball state.
 *******************************************************************/
#ifndef GOLF_LIB
#define GOLF_LIB

#include "golf_global.h"
#include "golf_input.h"
#include "golf_led.h"
#include "golf_lcd.h"
#include "golf_lcd_load.h"
#include "golf_lcd_print.h"
#include "golf_scene.h"
#include "golf_gameplay.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

enum sceneNames{NO_SCENE, TITLE, GAME, END, PAUSE, LOADING_TITLE, LOADING_GAME, LOADING_END, LOADING_PAUSE, LOADING};
/*Structure used for main scene switching*/
typedef struct{
    short gameScene;
}game_scenes;
game_scenes initGameSceneData();

enum loadedMap{NO_MAP, MAP1, MAP2, MAP3};
enum gameProcess{SETUP_GAME,INPUT_WAIT,CALC,NEXT_SWING,END_SWING,WIN_SWING,PAUSE_INPUT,PAUSE_CALC};
/*Structure used for all gameplay states*/
typedef struct{
    int mapPlaying, process;
    int numberOfSwings;
    float posX, posY, posZ;
    float v_X, v_Y, v_Z;
    float drag;
    int inAir;
    float windAcX, windAcY;
    float windAngle, windStrength;
    int waitWithDragBounce;
}ingame_states;
ingame_states initGameStateData();

enum ball_state{BALL_ALIVE, BALL_STOPED, BALL_DEAD, BALL_MIDAIR, BALL_WIN};

#endif