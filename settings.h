#ifndef SETTINGS_H
#define SETTINGS_H

#include "player.h"

/* define macros for magic numbers */ 
#define MSEC_IN_SEC (1000)
#define MSEC_TO_SEC(x) ((x)/(MSEC_IN_SEC))
#define Z_CAMERA_EYE (1500)
#define Z_NEAR (1)
#define Z_FAR  (2000)
#define CAMERA_ANGLE (60)
/* header file for specific animation settings that we 
 * can modify here */

/* gravity  y */
extern const float g_y;
/* animation const parameters */
extern const int timer_id;
extern const int timer_msec_interval;

typedef enum _game_mode{
    INIT    = 0,
    RESUMED = 1,
    PAUSED  = 2,
    STOP    = 3,
    QUIT    = 4
}game_mode;

typedef struct animation_settings{
    int animation_active; /* checking if our game is running */
    float animation_parameter; /* how fast does it go */
    game_mode gm;

}animation_settings;


void init_animation_settings(animation_settings *as);
void restart_game(player *p, animation_settings *as);
void pause_game(animation_settings *as);
void stop_game(player *p, animation_settings *as);
void print_game_status_info(player *p, animation_settings *as);


#endif