/*******************************************************************
  file: golf_input.c
  author: Matěj Navrátil

  Definitions of functions that reads and process input information
   and makes the information accessible from outside.
 *******************************************************************/
#include "golf_input.h"

extern unsigned char* mem_base;
mzapo_input game_input;
extern game_scenes game_scene;
extern ingame_states game_state;

/*Working with raw input data*/
mzapo_input initInputData(){
    mzapo_input ret;
    ret.init = false;
    ret.buttonRed = false;
    ret.buttonGreen = false;
    ret.buttonBlue = false;
    ret.buttonRedLast = false;
    ret.buttonGreenLast = false;
    ret.buttonBlueLast = false;
    ret.knobRed = 0;
    ret.knobGreen = 0;
    ret.knobBlue = 0;
    ret.knobRedLast = 0;
    ret.knobGreenLast = 0;
    ret.knobBlueLast = 0;
    return ret;
}
void getInputData(){
    mzapo_input ret = game_input;
    uint32_t rgb_knobs_value = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    /*buttons*/
    ret.buttonRedLast = ret.buttonRed;
    ret.buttonGreenLast = ret.buttonGreen; 
    ret.buttonBlueLast = ret.buttonBlue;
    ret.buttonRed = (rgb_knobs_value >> 26) & 0x1;
    ret.buttonGreen = (rgb_knobs_value >> 25) & 0x1;
    ret.buttonBlue = (rgb_knobs_value >> 24) & 0x1;

    /*encoders*/
    int Rk = (rgb_knobs_value >> 16) & 0xff;
    int Gk = (rgb_knobs_value >> 8) & 0xff;
    int Bk = (rgb_knobs_value) & 0xff;
    if(!ret.init){
        ret.knobRedLast = Rk;
        ret.knobGreenLast = Gk;
        ret.knobBlueLast = Bk;
        ret.init = true;
    }
    //on some board -= on some +=
    if(Rk != ret.knobRedLast)
        ret.knobRed -= incrementKnobValues(Rk, ret.knobRedLast);
    if(Gk != ret.knobGreenLast)
        ret.knobGreen -= incrementKnobValues(Gk, ret.knobGreenLast);
    if(Bk != ret.knobBlueLast)
        ret.knobBlue -= incrementKnobValues(Bk, ret.knobBlueLast);

    ret.knobRedLast = Rk;
    ret.knobGreenLast = Gk;
    ret.knobBlueLast = Bk;

    /*Red knob wraps its values*/
    if(ret.knobRed >= KNOB_ONE_ROTATION)
        ret.knobRed = ret.knobRed - KNOB_ONE_ROTATION;
    else if(ret.knobRed < KNOB_DEF_MIN)
        ret.knobRed = KNOB_ONE_ROTATION + ret.knobRed;
    
    /*Green knob doesn't wrap its values*/
    if(ret.knobGreen > KNOB_ONE_ROTATION)
        ret.knobGreen = KNOB_ONE_ROTATION;
    else if(ret.knobGreen < KNOB_DEF_MIN)
        ret.knobGreen = KNOB_DEF_MIN;
    
    /*Blue knob doesn't wrap its values*/
    if(ret.knobBlue >= GAME_BLUE_KNOB_MAX)
        ret.knobBlue = GAME_BLUE_KNOB_MAX;
    else if(ret.knobBlue < GAME_BLUE_KNOB_MIN)
        ret.knobBlue = GAME_BLUE_KNOB_MIN;
    
    game_input = ret;
}
int incrementKnobValues(int knobNow, int knobLast){
    int ret = 0;
    if(knobNow < knobLast)
    {
        if( (knobLast - knobNow) < KNOB_DEF_MAX/2 )
            ret += (knobLast - knobNow);
        else 
            ret -= KNOB_DEF_MAX - knobLast + knobNow-1;
    }
    else if(knobNow > knobLast)
    {
        if( (knobNow - knobLast) < KNOB_DEF_MAX/2 )
            ret -= (knobNow - knobLast) ;
        else 
            ret += knobLast + KNOB_DEF_MAX - knobNow+1;
    }
    return ret;
}

/*Accessing input information*/
bool setOnButtonRisingEdge(int knob){
    switch (knob)
    {
    case RED_KNOB:
        if(!game_input.buttonRedLast && game_input.buttonRed)
            return true;
        return false;
    case GREEN_KNOB:
        if(!game_input.buttonGreenLast && game_input.buttonGreen)
            return true;
        return false;
    case BLUE_KNOB:
        if(!game_input.buttonBlueLast && game_input.buttonBlue)
            return true;
        return false;
    case ALL_KNOBS:
        if(game_input.buttonRed && game_input.buttonBlue && game_input.buttonGreen 
            && (!game_input.buttonRedLast || !game_input.buttonBlueLast || !game_input.buttonGreenLast))
            return true;
        return false;
    default:
        return false;
        break;
    }
}
float getKnobGameValue(int knob){
    float ret = 0;
    float multiplier = 1;
    switch (knob)
    {
    case RED_KNOB:
        /*Without aretation*/
        multiplier = GAME_RED_KNOB_MULT;
        ret = multiplier * game_input.knobRed;
        break;
    case GREEN_KNOB:
        /*Without aretation*/
        multiplier = GAME_GREEN_KNOB_MULT;
        ret = multiplier * game_input.knobGreen;
        break;
    case BLUE_KNOB:
        /*With aretation*/
        ret = game_input.knobBlue /4;
        break;
    default:
        break;
    }
    return ret;
}
