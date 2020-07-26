#include "settings.h"
#include <stdlib.h>
#include <stdio.h>

const float g_y = -9.81f;
const int timer_id = 1;
const int timer_msec_interval = 20;

void init_animation_settings(animation_settings *as)
{
    /* setting parameters to default on run*/
    as->animation_active = 0;
    as->animation_parameter = 0;
    as->gm = INIT;

}
void restart_game(player *p, animation_settings *as)
{
    p->x_curr = 50;
    p->y_curr = 300;
    p->v_x = 10;
    p->v_y = 5;
    p->player_state = FALLING;
    p->jump_counter = 2;

    as->animation_parameter=0;
    as->animation_active=1;

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
    as->animation_parameter = 0;

}
void print_game_status_info(player *p, animation_settings *as)
{
    fprintf(stdout, "*************************************************************************\n");
	fprintf(stdout, "Information:\nBall (Player) at place (x: %f, y: %f, z: 1500).\n", p->x_curr, p->y_curr);
	fprintf(stdout, "Distance from ground: (%f).\nAnimation status: %d\nAnimation parameter: (%f)\nGame status: %d\n", p->y_curr, as->animation_active, as->animation_parameter, as->gm);
	/* create a specific check collision detection function for this */ 
	/*if(player_floor_collision(x_curr, y_curr, r)){
		fprintf(stdout, "*************************************************************************\n");
		fprintf(stdout, "Collision detected with floor: you lost!\n");
		fprintf(stdout, "*************************************************************************\n");

	}
	fprintf(stdout, "*************************************************************************\n");*/

}