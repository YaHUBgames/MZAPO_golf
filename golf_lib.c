/*******************************************************************
  file: golf_lib.c
  author: Matěj Navrátil

  Definitions of structure initializations.
 *******************************************************************/
#include "golf_lib.h"

ingame_states initGameStateData(){
    ingame_states ret;
    ret.mapPlaying = NO_MAP;
    ret.process = SETUP_GAME;
    ret.numberOfSwings = 0;
    ret.posX = 0;
    ret.posY = 0; 
    ret.posZ = 0;
    ret.v_X = 0;
    ret.v_Y = 0;
    ret.v_Z  = 0;
    ret.drag = 1;
    ret.inAir = 0;
    ret.windAcX = 0;
    ret.windAcY = 0;
    ret.windAngle = 0;
    ret.windStrength = 0;
    ret.waitWithDragBounce = 0;
    return ret;
}
game_scenes initGameSceneData(){
    game_scenes ret;
    ret.gameScene = NO_SCENE;
    return ret;
}
