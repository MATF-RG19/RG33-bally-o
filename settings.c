#include "settings.h"
#include <stdlib.h>
#include <stdio.h>


void init_animation_settings(animation_settings *as)
{
    /* setting parameters to default on run*/
    as->animation_active = 0;
    as->gm = INIT;

}

void resume_game(animation_settings *as)
{
    as->animation_active=1;
    as->gm=RESUMED;
}


void restart_game(player *p, animation_settings *as)
{
    p->x_curr = 50;
    p->y_curr = 300;
    p->v_x = 10;
    p->v_y = 5;
    p->player_state = STILL;    
    as->animation_active=0;
    as->gm=INIT;
}

void pause_game(animation_settings *as)
{
    as->gm = PAUSED;
    as->animation_active=0;

}

void stop_game(player *p, animation_settings *as)
{
    p->v_x = 0;
    p->v_y = 0;
    as->gm = STOP;
    as->animation_active = 0;
}

void quit_game()
{
    fprintf(stdout, "Exiting the game...\n");
    exit(EXIT_SUCCESS);
}

void print_game_status_info(player *p, animation_settings *as)
{

	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "Status: \n");
	fprintf(stdout, "Player position: (%f, %f,0)\nPlayer velocity: (%f, %f,0)\n", p->x_curr, p->y_curr, p->v_x, p->v_y);
	fprintf(stdout, "Player state: %s\nPlayer animation_parameter: %f\n", get_player_state(p), p->animation_parameter);
	fprintf(stdout, "Animation active: %s - Animation game mode: %s\n", ((as->animation_active) ? "yes" : "no"), get_game_mode(as));
	fprintf(stdout, "*******************************************\n");
}

const char* get_game_mode(animation_settings *as)
{
    switch(as->gm){
        case INIT:
            return "INIT";
        case RESUMED:
            return "RESUMED";
        case PAUSED:
            return "PAUSED";
        case STOP:
            return "STOP";
        case QUIT:
            return "QUIT";
        default:
            return "";
    }
}


