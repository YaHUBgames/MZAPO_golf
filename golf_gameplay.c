/*******************************************************************
  file: golf_gameplay.c
  author: Matěj Navrátil

  Definitions of reseting the game state and generating wind before 
  new game and simulation calculations for the golf ball.
 *******************************************************************/
#include "golf_gameplay.h"

game_scenes game_scene;
ingame_states game_state;

int calculateBall(){
    uint16_t groundType = drawBall((int)(roundf(game_state.posX)), (int)(roundf(game_state.posY)),(int)(roundf(game_state.posZ/4)));
    int returnState = BALL_ALIVE;

    if(game_state.waitWithDragBounce > 0){
        game_state.waitWithDragBounce = 0;
        if(game_state.v_Z > 1)
            game_state.posZ += 1.1f;
        returnState = BALL_MIDAIR;
        game_state.inAir = 0;
        game_state.drag = DRAG_FIELD_G;
        loadValueToLedRGB(RGB_LED_1, LED_WHITE);
    }

    /*movement calculations*/
    game_state.v_X = game_state.v_X + game_state.windAcX*game_state.windStrength*WIND_STRENGTH_CORRECTION*(TIME_INCREMENT)*game_state.inAir;
    game_state.v_X -= game_state.v_X * game_state.drag;
    game_state.posX += game_state.v_X*(TIME_INCREMENT)+
        (game_state.windAcX*game_state.windStrength*WIND_STRENGTH_CORRECTION/2)*(TIME_INCREMENT*TIME_INCREMENT)*game_state.inAir;

    game_state.v_Y = game_state.v_Y + game_state.windAcY*game_state.windStrength*WIND_STRENGTH_CORRECTION*(TIME_INCREMENT)*game_state.inAir; 
    game_state.v_Y -= game_state.v_Y * game_state.drag;
    game_state.posY += game_state.v_Y*(TIME_INCREMENT)+
        (game_state.windAcY*game_state.windStrength*WIND_STRENGTH_CORRECTION/2)*(TIME_INCREMENT*TIME_INCREMENT)*game_state.inAir;

    game_state.v_Z -= DOWN_AC*(TIME_INCREMENT)*game_state.inAir;
    game_state.posZ += game_state.v_Z*(TIME_INCREMENT) - (DOWN_AC/2)*(TIME_INCREMENT*TIME_INCREMENT)*game_state.inAir;

    /*ground check*/
    if(game_state.posZ <= 0 && game_state.waitWithDragBounce <= 0)
    {
        game_state.posZ=0;
        game_state.inAir = 0;

        /*stop bouncing*/
        if(abs((int)round(game_state.v_Z))<=1)
            game_state.v_Z = 0;

        /*bounciness and roll resistance*/
        switch (groundType)
        {
        case P_BLACK:
            returnState = BALL_WIN;
            DEBUG_SER_PRINT(" HIT HOLE ",0);
            break;
        case P_BLUE1:
        case P_BLUE2:
        case P_TRANSP:
            returnState = BALL_DEAD;
            game_state.v_Z *= - BOUNCE_WATER;
            game_state.drag = DRAG_WATER;
            loadValueToLedRGB(RGB_LED_1, LED_BLUE);
            DEBUG_SER_PRINT(" HIT WATER ",0);
            break;
        case P_GREEN4:
        case P_GREEN5:
        case P_GREEN6:
            game_state.v_Z *= - BOUNCE_TALL_G;
            game_state.drag = DRAG_TALL_G;
            loadValueToLedRGB(RGB_LED_1, LED_D_GREEN);
            DEBUG_SER_PRINT(" HIT TALL GRASS ",0);
            break;
        case P_YELLOW1:
        case P_YELLOW2:
            game_state.v_Z *= - BOUNCE_SAND;
            game_state.drag = DRAG_SAND;
            loadValueToLedRGB(RGB_LED_1, LED_YELLOW);
            DEBUG_SER_PRINT(" HIT SAND ",0);
            break;
        case P_GREEN1:
        case P_GREEN2:
        case P_GREEN3:
            game_state.v_Z *= - BOUNCE_FIELD_G;
            game_state.drag = DRAG_FIELD_G;
            loadValueToLedRGB(RGB_LED_1, LED_L_GREEN);
            DEBUG_SER_PRINT(" HIT FIELD GRASS ",0);
            break;
        default:
            DEBUG_SER_PRINT(" HIT default ",0);
            break;
        }
        
        /*STOP CALCULATION THRESHOLD*/
        if(returnState == BALL_ALIVE && abs((int)round(game_state.v_X*game_state.drag)) < 1 
            && abs((int)round(game_state.v_Y*game_state.drag)) < 1){
            returnState = BALL_STOPED;
            game_state.v_X = 0;
            game_state.v_Y = 0;
            DEBUG_SER_PRINT(" CALCULATION FINISHED ",0);
        }
    }else{
        returnState = BALL_MIDAIR;
        game_state.inAir = 1;
        game_state.drag = DRAG_AIR;
        loadValueToLedRGB(RGB_LED_1, LED_WHITE);
    }
    return returnState;
}

void resetState(){
    game_state.numberOfSwings = 0;

    game_state.posZ = 0;

    game_state.v_X = 0;
    game_state.v_Y = 0;
    game_state.v_Z = 0;

    game_state.drag = 0.00f;
    game_state.inAir = false;
    game_state.windAcX = 0.0f;
    game_state.windAcY = 0.0f;
    game_state.windAngle = 0;
    game_state.windStrength = 0;
    game_state.waitWithDragBounce = 3;
}

void generateWind(){
    game_state.windAngle = rand()%360;
    game_state.windStrength = 1+(rand()%(MAX_WIND_SPEED-1));
    game_state.windAcX = cos(toRad(game_state.windAngle));
    game_state.windAcY = sin(toRad(game_state.windAngle)); 
}
