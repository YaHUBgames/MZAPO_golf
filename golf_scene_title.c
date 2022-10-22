/*******************************************************************
  file: golf_scene_title.c
  author: Matěj Navrátil

  Defines title scene. It wait for button push and than sends request
  to load game with specific map.
 *******************************************************************/
#include "golf_scene.h"

extern mzapo_led_output game_led;
extern game_scenes game_scene;
extern ingame_states game_state;

void sceneTITLE(){
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    resetTempBuffer();
    resetGUIBuffer();

    /*Static scene load*/
    loadImageLCD(img_title_name, 126, 25, 3, BUFFER_TEMP);

    printStringLCD(&font_rom8x16, "Hole 1", 48, 270, 2, P_BLACK, BUFFER_TEMP);   
    printStringLCD(&font_rom8x16, "Hole 2", 192, 270, 2, P_BLACK, BUFFER_TEMP);  
    printStringLCD(&font_rom8x16, "Hole 3", 336, 270, 2, P_BLACK, BUFFER_TEMP);  

    loadRectLCD( 58, 260, 134, 184, 9, P_RED1, BUFFER_TEMP);
    loadRectLCD( 202, 260, 278, 184, 9, P_GREEN4, BUFFER_TEMP);
    loadRectLCD( 346, 260, 422, 184, 9, P_BLUE2, BUFFER_TEMP);

    loadImageLCD(img_map_icon_1, 66, 192, 3, BUFFER_TEMP);
    loadImageLCD(img_map_icon_2, 210, 192, 3, BUFFER_TEMP);
    loadImageLCD(img_map_icon_3, 354, 192, 3, BUFFER_TEMP);

    game_led = initLedData();
    setLedData();

    /*Input wait and animate background*/
    img_timeFlowReset(20);
    while(!game_state.mapPlaying)
    {
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

        loadBackgroundLCD(img_title_background);
        img_timeFlowTick();
        setLCD();

        getInputData();
        if(setOnButtonRisingEdge(RED_KNOB))
            game_state.mapPlaying = MAP1;
        if(setOnButtonRisingEdge(GREEN_KNOB))
            game_state.mapPlaying = MAP2;
        if(setOnButtonRisingEdge(BLUE_KNOB))
            game_state.mapPlaying = MAP3;
    }
    img_timeFlowReset(0);

    game_scene.gameScene = LOADING_GAME;
}
