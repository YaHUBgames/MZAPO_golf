/*******************************************************************
  file: golf_scene_end.c
  author: Matěj Navrátil

  Defines end(gameover) scene. It sets background and win/lose message
  based on to the conditions game scene was exited.
 *******************************************************************/
#include "golf_scene.h"

extern mzapo_led_output game_led;
extern game_scenes game_scene;
extern ingame_states game_state;

void sceneEND(){
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    resetTempBuffer();
    loadImageLCD(img_title_name, 164, 25, 2, BUFFER_TEMP);

    /*Chose background and win/lose message*/
    int backgroundType = img_lose_background;
    if( printWinLoseMSG())
        backgroundType = img_win_background;

    /*Set icon of map currently finished*/
    switch (game_state.mapPlaying)
    {
    case MAP1:
        loadImageLCD(img_map_icon_1, 210, 150, 3, BUFFER_TEMP);
        break;
    case MAP2:
        loadImageLCD(img_map_icon_2, 210, 150, 3, BUFFER_TEMP);
        break;
    case MAP3:
        loadImageLCD(img_map_icon_3, 210, 150, 3, BUFFER_TEMP);
        break;
    default:
        break;
    }

    /*Static scene load*/
    loadRectLCD( 0, 319, 138, 300, 11, P_RED1, BUFFER_TEMP);
    loadRectLCD( 479, 319, 390, 300, 11, P_BLUE1, BUFFER_TEMP);

    printStringLCD(&font_rom8x16, "End game", 5, 270, 2, P_WHITE, BUFFER_TEMP);
    printStringLCD(&font_rom8x16, "Title", 395, 270, 2, P_WHITE, BUFFER_TEMP);

    game_led.ledLine = 0x0;
    setLedData();

    /*Wait for input and animate background*/
    img_timeFlowReset(20);
    while(game_scene.gameScene == END)
    {
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

        loadBackgroundLCD(backgroundType);
        img_timeFlowTick();
        setLCD();

        getInputData();
        if(setOnButtonRisingEdge(RED_KNOB))
            game_scene.gameScene = NO_SCENE;
        if(setOnButtonRisingEdge(BLUE_KNOB))
            game_scene.gameScene = LOADING_TITLE;
    }
    img_timeFlowReset(0);
}

bool printWinLoseMSG(){
    int pointerToScoreMSG = 0; 
    bool didWin = false;
    if(game_state.process == END_SWING){
        /*If lost*/
        pointerToScoreMSG = 0;
        didWin = false;
        loadValueToLedRGB(BOTH_RGB_LEDS, LED_RED);
    }
    else if(game_state.numberOfSwings == 1){
        /*If won after one swing*/
        pointerToScoreMSG = 1;
        didWin = true;
        loadValueToLedRGB(BOTH_RGB_LEDS, LED_YELLOW);
    }
    else{
        /*Won, but after more than one swing*/
        int relativeParScore = 0;
        switch (game_state.mapPlaying)
        {
        case MAP1:
            relativeParScore = MAP1_PAR_RATING;
            break;
        case MAP2:
            relativeParScore = MAP2_PAR_RATING;
            break;
        case MAP3:
            relativeParScore = MAP3_PAR_RATING;
            break;
        default:
            break;
        }

        /*Get correct message*/
        relativeParScore = game_state.numberOfSwings - relativeParScore;
        if(relativeParScore >= -5 && relativeParScore <= 4)
            while (SCORE_NAMES[++pointerToScoreMSG].stokesThanPar != relativeParScore){DEBUG_SER_PRINT("MSG pointer ==",pointerToScoreMSG);}
        else
            pointerToScoreMSG = 11;
        
        didWin = true;
        loadValueToLedRGB(BOTH_RGB_LEDS, LED_D_GREEN);
    }
    printStringLCD(&font_winFreeSystem14x16, SCORE_NAMES[pointerToScoreMSG].name,
        LCD_WIDTH/2 - (getStringFontLength(&font_winFreeSystem14x16, SCORE_NAMES[pointerToScoreMSG].name , 2)/2) , 230,
        2, P_BLACK, BUFFER_TEMP);
    return didWin;
}
