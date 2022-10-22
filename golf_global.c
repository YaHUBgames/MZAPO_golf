/*******************************************************************
  file: golf_global.c
  author: Matěj Navrátil

  Definition of DEBUG messaging system and mzapo peripherals access.
 *******************************************************************/
#include "golf_global.h"

/*Access to mzapo peripherals*/
unsigned char* mem_base;
unsigned char* parlcd_mem_base;

void DEBUG_SER_PRINT(char* c, int p)
{
    #ifdef DEBUG
    printf("\n%s ->%d",c,p);
    #endif
}