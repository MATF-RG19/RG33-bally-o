#include "helper.h"
#include "player.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "collision.h"


const float g_y = -9.81f;
const int timer_id = 1;
const int timer_msec_interval = 30;

void init_player(player *p)
{
	p->r = 40.0f;
	p->x_curr = 0.0f;
	p->y_curr = 0.0f;
	p->v_x = 20.0f;
	p->v_y = 5.0f;
	p->jump_counter=2;
	p->player_state=ROLLING_RIGHT;
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


void move_left(player *p)
{
	p->animation_parameter-=10;
	p->v_x -= g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	p->x_curr -= p->v_x;
	p->v_y -= g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	p->y_curr -= p->v_y;
	/* collision checks */


}
void move_right(player *p)
{
	p->animation_parameter+=10;
	p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	p->x_curr += p->v_x;
	p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	p->y_curr -= 5*p->v_y;
	/* collision checks */
	/* todo: write a unifed collison check function */
	//player_floor_collision_event(p);
}
void jump(player *p){
	

	if(p->player_state == JUMPING){
		p->animation_parameter += 10;
		p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
		p->y_curr +=  10*p->v_y;
		if(p->y_curr > 400){
			p->player_state = ROLLING_RIGHT;
		}
		else if(p->player_state == ROLLING_RIGHT){
			p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
			p->y_curr -=  p->v_y;
		}
	}

	
	// p->animation_parameter+=10;
	// p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	// p->x_curr += 2*p->v_x;
	// p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	// p->y_curr += 2*p->v_y;
	/* collision checks */
}