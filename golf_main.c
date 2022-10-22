/*******************************************************************
  file: golf_main.c
  author: Matěj Navrátil

  Main source file for mzapo golf game. Contains state machine for
  scene switching
 *******************************************************************/
#define _POSIX_C_SOURCE 200112L

#include "golf_lib.h"

extern unsigned char* mem_base;
extern unsigned char* parlcd_mem_base;
extern mzapo_input game_input;
extern mzapo_led_output game_led;
extern mzapo_lcd_output game_lcd;
extern game_scenes game_scene;
extern ingame_states game_state;

/*Must be triggered before anything else*/
void Start();
/*Must be triggered after everything else*/
void OnLeave();

int main(int argc, char *argv[]) {
  
    /*Must be first*/
    Start();
    
    while(game_scene.gameScene != NO_SCENE)
    {
        switch (game_scene.gameScene)
        {
        case TITLE:
            sceneTITLE();
            break;
        case GAME:
            sceneGAME();
            break;
        case END:
            sceneEND();
            break;
        case PAUSE:
            scenePAUSE();
            break;
        default:
            sceneLOADING();
            break;
        }
    }

    /*Must be last*/
    OnLeave();

    return 0;
}

/*Must be triggered before anything else.*/
void Start(){
    /*Setup access to peripherals and lcd*/
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (mem_base == NULL)
        exit(1);
    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL)
        exit(1);  
    
    srand(time(NULL));
    /*initialize all global data*/
    img_timeFlowReset(0);
    //parlcd_hx8357_init(parlcd_mem_base);
    game_input = initInputData();
    game_led = initLedData();
    game_lcd = initLcdData();
    game_scene = initGameSceneData();
    game_state = initGameStateData();

    /*send/gets all data to/from mzapo*/
    getInputData();
    setLedData();
    setLCD();
    
    /**/
    game_scene.gameScene = LOADING_TITLE;
}
/*Must be triggered after everything else*/
void OnLeave(){
    free(game_lcd.lcdBuffer);
    free(game_lcd.tempBuffer);
    free(game_lcd.GUIbuffer);
}
