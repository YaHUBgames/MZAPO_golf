/*******************************************************************
  file: golf_scene.h
  author: Matěj Navrátil

  Declarations of all scenes.
 *******************************************************************/
#ifndef GOLF_SCENE
#define GOLF_SCENE

#include "golf_global.h"

#include "golf_lib.h"

#include <time.h>
#include <stdbool.h>

/*Title and map selection*/
void sceneTITLE();
/*Whole game logic*/
void sceneGAME();
/*Gameover scene, msg on score*/
void sceneEND();
/*Pause game scene*/
void scenePAUSE();
/*Loading scene - waits for LOADING_SCREEN_WAIT seconds*/
void sceneLOADING();
/*End of loading scene setup*/
void loadingFinishedSetup();
/*End scene message*/
bool printWinLoseMSG();

#endif
