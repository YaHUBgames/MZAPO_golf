/*******************************************************************
  file: golf_scene_game.c
  author: Matěj Navrátil

  Defines game scene. It is divided into input read and simulation
  calculations. From both it is possible to pause.
 *******************************************************************/
#include "golf_scene.h"

extern mzapo_input game_input;
extern mzapo_led_output game_led;
extern mzapo_lcd_output game_lcd;
extern game_scenes game_scene;
extern ingame_states game_state;

void sceneGAME(){
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    resetTempBuffer();
    resetGUIBuffer();
    game_lcd.useGUI = true;
    int map = NO_MAP;
    int flagPosX = 0; 
    int flagPosY = 0;
    switch (game_state.mapPlaying)
    {
    case MAP1:
        map = img_map1_background;
        if(game_state.process == SETUP_GAME){
            game_state.posX = MAP1_POSX;
            game_state.posY = MAP1_POSY;
        }
        flagPosX = MAP1_FLAGX;
        flagPosY = MAP1_FLAGY;
        break;
    case MAP2:
        map = img_map2_background;
        if(game_state.process == SETUP_GAME){
            game_state.posX = MAP2_POSX;
            game_state.posY = MAP2_POSY;
        }
        flagPosX = MAP2_FLAGX;
        flagPosY = MAP2_FLAGY;
        break;
    case MAP3:
        map = img_map3_background;
        if(game_state.process == SETUP_GAME){
            game_state.posX = MAP3_POSX;
            game_state.posY = MAP3_POSY;
        }
        flagPosX = MAP3_FLAGX;
        flagPosY = MAP3_FLAGY;
        break;
    default:
        break;
    }
    loadBackgroundLCD(map);

    switch (game_state.process)
    {
    case PAUSE_CALC:
        game_state.process = CALC;
        break;
    case SETUP_GAME:
        resetState();
        generateWind();
    case PAUSE_INPUT:
    default:
        game_state.process = INPUT_WAIT;
        break;
    }
    /*************************************************** GAME LOOP *****************/
    while (game_state.process < NEXT_SWING)
    {
        /*************************************************** INPUT LOOP *****************/
        while (game_state.process == INPUT_WAIT)
        {   
            resetTempBuffer();
            resetGUIBuffer();
            getInputData();

            printNumberLCD(&font_rom8x16,(int)game_state.windStrength,52,15,2,P_WHITE,BUFFER_GUI);
            printNumberLCD(&font_rom8x16,(int)game_state.numberOfSwings,450,10,2,P_WHITE,BUFFER_GUI);
            loadImageLCD(img_hole_flag,flagPosX,flagPosY,1,BUFFER_TEMP);
            loadArrowLCD(26,26,game_state.windAcX,game_state.windAcY,25,1,true,P_WHITE,BUFFER_GUI);

            int knobG = getKnobGameValue(GREEN_KNOB);
            int knobR = getKnobGameValue(RED_KNOB);
            game_led.ledLine = getLedLineFromNum((int)round(knobG));
            
            if(knobG <= 17)
                loadArrowLCD(game_state.posX,game_state.posY,cos(toRad(knobR)),sin(toRad(knobR)),20+knobG*2,1,false,P_BLACK,BUFFER_TEMP);
            else
                loadArrowLCD(game_state.posX,game_state.posY,cos(toRad(knobR)),sin(toRad(knobR)),20+(knobG-16)*2,1,false,P_RED1,BUFFER_TEMP);
            
            drawBall((int)(roundf(game_state.posX)), (int)(roundf(game_state.posY)),(int)(roundf(game_state.posZ/4)));

            game_led.ledRGB1 = LED_BLACK;
            game_led.ledRGB2 = LED_D_GREEN;
            setLedData();
            
            setToZoomBufferLCD((int)getKnobGameValue(BLUE_KNOB), (int)game_state.posX, (int)game_state.posY);

            /*Set initial swing contitions*/
            if(setOnButtonRisingEdge(BLUE_KNOB))
                game_state.process = PAUSE_INPUT;
            else if(setOnButtonRisingEdge(RED_KNOB)){
                game_state.process = CALC;
                resetTempBuffer();
                game_state.numberOfSwings++;
                game_state.waitWithDragBounce = 3;
                game_state.v_X = cos(toRad(knobR));
                game_state.v_Y = sin(toRad(knobR));
                if(knobG <= 17){
                    game_state.v_Z = 0;
                    game_state.v_X *= 3 + knobG*2;
                    game_state.v_Y *= 3 + knobG*2;
                }
                else{
                    game_state.v_Z = UP_V;
                    game_state.v_X *= 1 + (knobG-16)*2;
                    game_state.v_Y *= 1 + (knobG-16)*2;
                }
                    
            }
        }
        /*************************************************** CALCULATION LOOP *****************/
        while (game_state.process == CALC)
        {
            clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
            int ballState = calculateBall();

            game_led.ledLine = getLedLineFromNum((int)sqrt(game_state.v_X *game_state.v_X + game_state.v_Y * game_state.v_Y));
            game_led.ledRGB2 = LED_RED;

            setLedData();
            setToZoomBufferLCD((int)getKnobGameValue(BLUE_KNOB), (int)game_state.posX, (int)game_state.posY);

            getInputData();
            if(setOnButtonRisingEdge(BLUE_KNOB))
              game_state.process = PAUSE_CALC;
            switch (ballState)
            {
            case BALL_STOPED:
              game_state.process = NEXT_SWING;
              break;
            case BALL_WIN:
              game_state.process = WIN_SWING;
              break;
            case BALL_DEAD:
              game_state.process = END_SWING;
              break;
            }
        }
        if(game_state.process == NEXT_SWING){
            game_state.process = INPUT_WAIT;
        }
    }

    switch (game_state.process)
    {
    case END_SWING:
    case WIN_SWING:
        game_scene.gameScene = LOADING_END;
        break;
    case PAUSE_INPUT:
    case PAUSE_CALC:
        game_scene.gameScene = PAUSE;
        break;
    default:
        game_scene.gameScene = NO_SCENE;
        break;
    }
    game_lcd.useGUI = false;
}
