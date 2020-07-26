#include "helper.h"
#include "player.h"
#include "settings.h"



void draw_ball(float r, float x, float y, float animation_parameter)
{
	glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(animation_parameter, 0, 0, -1);
		glColor3f(1,0,0);
		glScalef(r,r,r);
		draw_sphere();
	glPopMatrix();
}