#ifndef SETTINGS_H
#define SETTINGS_H

#include "player.h"
/* #include "map.h" */
/* #include "collision.h" */

/* define macros for magic numbers */ 
#define Z_CAMERA_EYE (1500)
#define Z_NEAR (1)
#define Z_FAR  (2000)
#define CAMERA_ANGLE (60)
#define START_WINDOW_WIDTH_SIZE (600)
#define START_WINDOW_HEIGHT_SIZE (600)
#define START_WINDOW_POS_X (100)
#define START_WINDOW_POS_Y (100)


/* header file for specific animation settings that we 
 * can modify here */


typedef enum _game_mode{
    INIT    = 0,
    RESUMED = 1,
    PAUSED  = 2,
    STOP    = 3,
    QUIT    = 4
}game_mode;

typedef struct animation_settings{
    int animation_active; /* checking if our game is running */
    game_mode gm;

}animation_settings;

void init_animation_settings(animation_settings *as);
void resume_game(animation_settings *as);
void restart_game(player *p, animation_settings *as);
void pause_game(animation_settings *as);
void stop_game(player *p, animation_settings *as);
void quit_game(void);
void print_game_status_info(player *p, animation_settings *as);


#endif