#include "helper.h"
#include "player.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


const float g_y = -9.81f;
const int timer_id = 1;
const int timer_msec_interval = 20;

void init_player(player *p)
{
	p->r = 50.0f;
	p->x_curr = 50.0f;
	p->y_curr = 300.0f;
	p->v_x = 10.0f;
	p->v_y = 5.0f;
	p->jump_counter=2;
	p->player_state=ROLLING;
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
		glScalef(p->r,p->r,p->r);
		draw_sphere();
	glPopMatrix();
}


void move_left(player *p)
{
	p->animation_parameter-=10;
	p->v_x -= g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	p->x_curr -= p->v_x;
	p->v_y -= g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	p->y_curr -= p->v_y;
	// if(player_floor_collision(x_curr, y_curr, r)){
	// 	/* stop the animation if it falls under */
	// 	player_floor_collision_event(x_curr, y_curr, r);
	// }
	// if(player_tile_collision(x_curr, y_curr, r)){
	// 	/* stop the animation if it falls under */
	// 	player_tile_collision_event(x_curr, y_curr, r);
	// }

}
void move_right(player *p)
{
	p->animation_parameter+=10;
	p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	p->x_curr += 10*p->v_x;
	p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	p->y_curr -= p->v_y;
}
void jump(player *p){
	
	p->animation_parameter+=10;
	p->v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	p->x_curr += 20*p->v_x;
	p->v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
	p->y_curr += 20*p->v_y;


}