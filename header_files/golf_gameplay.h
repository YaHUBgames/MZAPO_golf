/*******************************************************************
  file: golf_gameplay.h
  author: Matěj Navrátil

  Declares functions accessing the game state and functions that
  use this data and loads simulation of a moving ball to LCD buffers.
 *******************************************************************/
#ifndef GOLF_GAMEPLAY
#define GOLF_GAMEPLAY

#include "golf_global.h"
#include "golf_lib.h"

/*Ball physics calculations*/
int calculateBall();

/*Other functions*/

void resetState();
void generateWind();

#endif