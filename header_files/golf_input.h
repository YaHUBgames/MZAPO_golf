/*******************************************************************
  file: golf_input.h
  author: Matěj Navrátil

  Declaration of structure holding all input data and functions to
  access it.
 *******************************************************************/
#ifndef GOLF_INPUT
#define GOLF_INPUT

#include "golf_global.h"

#include "golf_lib.h"
#include "font_types.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct{
    bool buttonRed, buttonGreen, buttonBlue;
    bool buttonRedLast, buttonGreenLast, buttonBlueLast;
    int knobRed,knobGreen, knobBlue;
    int knobRedLast, knobGreenLast, knobBlueLast;
    bool init;
}mzapo_input;

/*Working with raw input data*/
mzapo_input initInputData();
void getInputData();
int incrementKnobValues(int knobNow, int knobLast);

/*Accessing input information*/
enum knobID {RED_KNOB, GREEN_KNOB, BLUE_KNOB, ALL_KNOBS};
bool setOnButtonRisingEdge(int knob);
float getKnobGameValue(int knob);

#endif