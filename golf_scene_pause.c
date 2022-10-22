/*******************************************************************
  file: golf_scene_pause.c
  author: Matěj Navrátil

  Defines pause scene. From here player can return to title or
  continue playing. 
 *******************************************************************/
#include "golf_scene.h"

extern mzapo_led_output game_led;
extern game_scenes game_scene;
extern ingame_states game_state;

void scenePAUSE(){
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    resetTempBuffer();
    resetGUIBuffer();

    /*Static scene load*/
    loadImageLCD(img_title_name, 126, 25, 3, BUFFER_TEMP);  

    loadRectLCD( 0, 319, 138, 300, 11, P_RED1, BUFFER_TEMP);
    loadRectLCD( 479, 319, 390, 300, 11, P_BLUE1, BUFFER_TEMP);

    printStringLCD(&font_rom8x16, "Paused", 192, 200, 2, P_WHITE, BUFFER_TEMP);
    printStringLCD(&font_rom8x16, "Continue", 5, 270, 2, P_WHITE, BUFFER_TEMP);
    printStringLCD(&font_rom8x16, "Leave", 395, 270, 2, P_WHITE, BUFFER_TEMP);

    game_led = initLedData();
    setLedData();

    /*Wait for input and animate background*/
    img_timeFlowReset(20);
    while(game_scene.gameScene == PAUSE){
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

        loadBackgroundLCD(img_pause_background);
        img_timeFlowTick();
        setLCD();

        getInputData();
        if(setOnButtonRisingEdge(RED_KNOB))
            game_scene.gameScene = GAME;
        if(setOnButtonRisingEdge(BLUE_KNOB)){
            game_scene.gameScene = LOADING_TITLE;
            game_state.mapPlaying = NO_MAP;
        }
    }
    img_timeFlowReset(0);
}
