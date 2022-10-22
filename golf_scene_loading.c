/*******************************************************************
  file: golf_scene_loading.c
  author: Matěj Navrátil

  Definition of loading scene. If needed setups corect values for 
  next scene. Special behaviour for all button pushed at the same 
  time: exits the application.
 *******************************************************************/
#include "golf_scene.h"

extern game_scenes game_scene;
extern ingame_states game_state;

void sceneLOADING(){
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    resetTempBuffer();
    resetGUIBuffer();

    /*Static scene setup*/
    if(game_scene.gameScene != LOADING_TITLE)
        loadImageLCD(img_title_name, 126, 25, 3, BUFFER_TEMP);
    loadBackgroundLCD(img_loading_background);

    printStringLCD(&font_rom8x16, "Loading", 295, 285, 2, P_WHITE, BUFFER_TEMP);

    /*Load wait loop*/
    img_timeFlowReset(getImgDef(img_loading_dots).img_anim_T);
    for (int i = 0; i < LOADING_SCREEN_WAIT; i++){
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

        loadImageLCD(img_loading_dots,420,297,1, BUFFER_MAIN);
        setLCD();

        getInputData();
        if(setOnButtonRisingEdge(ALL_KNOBS)){
            game_scene.gameScene = NO_SCENE;
            return;
        }
    }
    img_timeFlowReset(0);

    loadingFinishedSetup();
}

void loadingFinishedSetup(){
    switch (game_scene.gameScene)
    {
    case LOADING_TITLE:
        resetState();
        game_state.mapPlaying = NO_MAP;
        game_scene.gameScene = TITLE;
        break;
    case LOADING_GAME:
        game_state.process = SETUP_GAME;
        game_scene.gameScene = GAME;
        break;
    case LOADING_END:
        game_scene.gameScene = END;
        break;
    case LOADING_PAUSE:
        game_scene.gameScene = PAUSE;
        break;
    case LOADING:
    default:
        game_scene.gameScene = NO_SCENE;
        break;
    }
}
