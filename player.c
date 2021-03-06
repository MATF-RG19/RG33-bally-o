#include "helper.h"
#include "player.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "collision.h"
#include "map.h" 

const float g_y = 9.81f;
const int timer_id = 1;
const int timer_msec_interval = 20;

void init_player(player *p)
{
	p->x_curr = 0;
	p->y_curr = 0;
	p->r = 20.0f;
	p->v_x = 10.0f;
	p->v_y = 5.0f;
	p->jump_height = 120.0f;
	p->player_state=STILL;
	p->animation_parameter=0;
}

void draw_ball(player *p)
{
	glPushMatrix();
		GLfloat ambient[] = {0.3,0.3,0.3,0};
		GLfloat diffuse[] = {0,0.7,0,0};
		GLfloat specular[] = {0.6,0.6,0.6,0};
		GLfloat shininess = 80;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glTranslatef(p->x_curr, p->y_curr, 0);
		glRotatef(p->animation_parameter, 0, 0, -1);
		glColor3f(1,0,0);
		draw_sphere(p->r);
	glPopMatrix();
}

const char* get_player_state(player *p){
	switch(p->player_state){
		case STILL:
			return "STILL";
		case ROLLING_RIGHT:
			return "ROLLING_RIGHT";
		case JUMPING:
			return "JUMPING";
		case FALLING:
			return "FALLING";
		case ROLLING_LEFT:
			return "ROLLING_LEFT";
		case DEATH:
			return "DEATH";
		default:
			return "";
	}
}

void still(player *p){
	if(p->player_state == STILL){
		p->v_x = (!collision_tile_flag) ? 0 : p->v_x;
		p->v_y = (collision_tile_flag) ? 0 : p->v_y;
	}
}

void move_left(player *p)
{
	if(p->player_state == ROLLING_LEFT){
		p->animation_parameter-=10; /* rolling in reverse */
		p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2.0f;
		p->x_curr -= p->v_x;

	}
}
void move_right(player *p)
{
	if(p->player_state == ROLLING_RIGHT){
		p->animation_parameter+=10;
		p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2.0f;
		p->x_curr += p->v_x;

	}
}
void jump(player *p){
	
	if(p->player_state == JUMPING){
		p->animation_parameter += 5; /* slow down rotation parameter of the ball, so that we can simulate air friction */
		p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval) / 2.0f;
		p->y_curr +=  p->v_y;
		if(p->y_curr  > p->jump_height){
			p->player_state = FALLING;
		}
	}
	else if(p->player_state == FALLING){
		p->animation_parameter += 30;
		p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval) / 2.0f;
		p->y_curr -=   p->v_y;
	}
}

void death(player *p)
{
    player_floor_collision_event(p);
}
