[//]: # (This file won't work correctly if it is outside project directory. Please open the one inside of the directory with an compatible application)

# MZAPO GOLF GAME

## Intro
This project is final work for course B0B35APO. It contains all required source files needed to successfully compile and run the application on mzapo board.

Mzapo golf is based on [mzapo_template](https://gitlab.fel.cvut.cz/b35apo/mzapo_template.git) project and cannot work without mzapo board. All technical information about mzapo board can be found on [official site](https://cw.fel.cvut.cz/wiki/courses/b35apo/en/documentation/mz_apo/start).

<ins>Note</ins>: this file won't work correctly if it is outside project directory.

## Compile and run
Makefile works the same way as the one from the template. Before running the application on board you will need to change or comment these two lines. 
```bash
[28] SSH_OPTIONS=-i /opt/zynq/ssh-connect/mzapo-root-key
[29] SSH_OPTIONS=-o 'ProxyJump=ctu_login@postel.felk.cvut.cz'
```

Using this command will build the application and run it on the board.
```bash
$ make run TARGET_IP=192.168.XXX.XXX
```
For better explanation on how to connect to mzapo board use [official tutorial site](https://cw.fel.cvut.cz/wiki/courses/b35apo/en/documentation/mz_apo-howto/start)

## Code structure
This project is separated into individual source and header files:
### The global part
- [golf_main.c](##golf_main.c)
- [golf_lib.c](##golf_lib.c)    /   [golf_lib.h](##golf_lib.h)
- [golf_global.c](##golf_global.c)  /   [golf_global.h](##golf_global.h)
- [golf_assets.c](##golf_assets.c)  /   [golf_assets.h](##golf_assets.h)
- [golf_imagebmp.c](##golf_imagebmp.c)  /   [golf_imagebmp.h](##golf_imagebmp.h)

### Peripheral access
- [golf_input.c](##golf_input.c)    /   [golf_input.h](##golf_input.h)
- [golf_led.c](##golf_led.c)    /   [golf_led.h](##golf_led.h)
- [golf_lcd.c](##golf_lcd.c)    /   [golf_lcd.h](##golf_lcd.h)

### Working with data from/for peripherals
- [golf_lcd_load.c](##golf_lcd_load.c)  /   [golf_lcd_load.h](##golf_lcd_load.h)
- [golf_lcd_print.c](##golf_lcd_print.c)    /   [golf_lcd_print.h](##golf_lcd_print.h)
- [golf_gameplay.c](##golf_gameplay.c)  /   [golf_gameplay.h](##golf_gameplay.h)

### Game scenes
- [golf_scene.h](##golf_scene.h)
- [golf_scene_loading.c](##golf_scene_loading.c)
- [golf_scene_title.c](##golf_scene_title.c)
- [golf_scene_game.c](##golf_scene_game.c)
- [golf_scene_pause.c](##golf_scene_pause.c)
- [golf_scene_end.c](##golf_scene_end.c)

# Source files

### golf_main.c
[Open file](golf_main.c)

Contains enumerator based scene state machine, startup and exit setups.

## golf_lib.c
[Open file](golf_lib.c)

Is used only for definitions of game state and game scene structure initializations.

## golf_global.c
[Open file](golf_global.c)

Globally needed variables for accessing mzapo board peripherals and Debug messaging system are defined here. Debug message function is written in a way that it prints only when `DEBUG` is defined.

## golf_assets.c
[Open file](golf_assets.c)

Definitions for all texture and image functions. Images are defined here with their properties and functions accessing the stored bitmap data. Some textures and some images do have global variable inside them that makes animating them possible. Maps have one global variable for themselves that is responsible for jittering edge of field textures.

If you are adding new image you need to define image definition `_img_def` and also allow access to this information from outside by adding case in function:
```bash
_img_def getImgDef(int img){
    ...
    case img_new_image_ID:
		return i_new_image_definition;
    ...
}
```

## golf_imagebmp.c
[Open file](golf_imagebmp.c)

Definitions for all bitmap images and saving reference to them to a globally accessible pointers.

## golf_input.c
[Open file](golf_input.c)

Definitions of functions that work with input data. Function to get all input data from mzapo board and process it. It also maps the data so by calling this function in code:
```bash
getKnobGameValue(RED_KNOB);
```
You will get a number from 0 to 360 mapped to one knob rotation.

## golf_led.c
[Open file](golf_led.c)

Functions that work with LED data and with mzapo LEDs are defined here.

## golf_lcd.c
[Open file](golf_lcd.c)

Definition of functions allocating memory for LCD buffers, working with them and setting this data to mzapo LCd screen. There are two types of set functions, one normal that send everything in buffer to the screen and one that sends zoomed main and temporary buffers while sending GUI buffer normally.

## golf_lcd_load.c
[Open file](golf_lcd_load.c)

Defines all functions loading images, textures and primitive shapes to LCD buffers. It works directly with `golf_assets` files. If there is need for new image or texture you need to define it in `golf_assets` (if it is bitmap also in `golf_imagebmp`) and then add access to thi image by adding case inside the correct function.
```bash
void loadImageLCD(...){
    ...
    case img_new_image_ID:
        ret = I_new_image_function(width, height);
    break;
    ...
}
```

## golf_lcd_print.c
[Open file](golf_lcd_print.c)

It defines all functions working with fonts that were part of the template. The functions should work with any font that is declared in `font_types.h`

## golf_gameplay.c
[Open file](golf_gameplay.c)

This file defines the core simulation of gold ball movement. All customizable data are stored in `golf_global.h`. If you want to add new ground type you want to define colors and background in `golf_assets` files, define behavior variables like drag and bounce in `golf_global.h` and then add case for corresponding colors and values:
```bash
int calculateBall(){
    ...
    /*bounciness and roll resistance*/
    ...
    case P_NEW_GROUND_COLOR1:
    case P_NEW_GROUND_COLOR2:
        game_state.v_Z *= - BOUNCE_NEW_GROUND;
        game_state.drag = DRAG_NEW_GROUND;
        loadValueToLedRGB(RGB_LED_1, LED_NEW_GROUND_COLOR);
        ...
        break;
    ...
}
```
## golf_scene_loading.c
[Open file](golf_scene_loading.c)

First scene you will see is loading. It serves as middle man if something needs to be set between two scenes this is the place to do it. There is special behavior for pressing all three buttons at once. It will correctly exit the application. 

## golf_scene_title.c
[Open file](golf_scene_title.c)

Title scene shows the title image and three icons for three maps. Pressing corresponding button will load that map. Currently it is made so only three maps can be accessed in the game.

## golf_scene_game.c
[Open file](golf_scene_game.c)

Game scene loads map, ball, hole flag and all GUI to LCD buffers. First it waits for inputs and for red button confirmation. Then it calculates the ball movement and loads it to the buffers. After calculations are finished is is back to input wait.

## golf_scene_pause.c
[Open file](golf_scene_pause.c)

Simple "Paused" text on moving background. It is possible to continue the game or return to title scene and chose different map.

## golf_scene_end.c
[Open file](golf_scene_end.c)

Win or lose this will be the scene player sees. Background and RGB LEDs changes based on win/lose conditions. Messages are stored in `golf_assets`.



# Header files

## golf_lib.h
[Open file](header_files/golf_lib.h)

This is used as a container for the rest of header files. That way everything needed can be included just by including this file. There are defined enumerators and structures for tracking state of scene switching, state of gameplay loop and current map ID. Enumerator for state of the ball that is used in ball movement simulations is defined here too.

## golf_global.h
[Open file](header_files/golf_global.h)

Declarations of globally important program values. Size of LCD screen, height of GUI buffer in game view, definition of encoders one rotation value and its maximum and minimum value, specific multiplier for encoders for converting one rotation value to corresponding game value. Game map rating, hole positions, ball starting positions, and physic values like bounciness, wind speed ect. are all defined here.
This file also links template libraries for mzapo peripherals and commented declaration of `DEBUG` that serves as toggleable debug system.

## golf_assets.h
[Open file](header_files/golf_assets.h)

Serves as a storage for all things like LCD colors, textures, LED colors and text constants that are used throughout the project. Textures (identified by enumerator `backgroundImages`) are not stored as bit maps or any other picture format they are pre-defined functions that will return one specific color based on pixel position. With that there are few definitions for making these textures easier. Images (with enumerator `smallImages`) are not full screen and most of them are stored as bitmaps in `golf_imagebmp` files.

## golf_imagebmp.h
[Open file](header_files/golf_imagebmp.h)

Declaration of pointer to stored bitmap images.

## golf_input.h
[Open file](header_files/golf_input.h)

Declaration of structure holding all input data and functions to read, process and access it. Defined enumerator is used for identifying all knobs.

## golf_led.h
[Open file](header_files/golf_led.h)

Declaration of structure holding all information about LEDs.  There are also declared functions to set the data to mzapo board. One macro to convert individual RGB values to one uint32_t value and one for converting a number to corresponding uint32_t LED line representation.

## golf_lcd.h
[Open file](header_files/golf_lcd.h)

Declaration of structure holding LCD buffer information and all functions accessing it.

## golf_lcd_load.h
[Open file](header_files/golf_lcd_load.h)

Functions that are used to fill LCD buffers with textures, images or primitive shapes are all defined here.

## golf_lcd_print.h
[Open file](header_files/golf_lcd_print.h)

Declares all functions working with fonts and loading characters, strings and numbers to LCD buffers. There is also function to get pixel width of a string. This it to allow, for example printing unknown word correctly in the middle.

## golf_gameplay.h
[Open file](header_files/golf_gameplay.h)

It declares functions that use game state data to load golf ball simulations to LCD buffers.

## golf_scene.h
[Open file](header_files/golf_scene.h)

Declares all different scenes.