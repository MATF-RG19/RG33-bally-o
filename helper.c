/* system headers */ 
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/* user headers */ 
#include "helper.h"


int animation_helper = 0;
const float m_pi = 3.1415926535f;
const float m_eps = 0.01f;


void error_msg(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void set_normal_and_vertex(float u, float v)
{
	glNormal3f(sin(u) * sin(v), cos(u), sin(u) * cos(v));
	glVertex3f(sin(u) * sin(v), cos(u), sin(u) * cos(v));
}

void draw_sphere()
{
	glPushMatrix();
		for(float u = 0.0f; u < m_pi; u += m_pi / 20.0f){
			glBegin(GL_TRIANGLE_STRIP);
				for(float v = 0.0f; v <= m_pi*2 + m_eps; v += m_pi/ 20.0f){
					set_normal_and_vertex(u, v);
					set_normal_and_vertex(u + m_pi / 20.0f, v);
				}
			glEnd();
		}
	glPopMatrix();
}

void draw_plane(float len)
{
    glDisable(GL_LIGHTING);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex3f(len, 0, 0);
		glVertex3f(-len, 0, 0);
		glVertex3f(0, 0, -len);
		glVertex3f(0, 0, len);
	glEnd();
    glEnable(GL_LIGHTING);

}

void draw_coord(float len)
{
    glDisable(GL_LIGHTING);
	glLineWidth(DEFAULT_LINE_WIDTH);
	glBegin(GL_LINES);
		/* x - axis - red */ 
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(len,0,0);
		/* y - axis - green */
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,len,0);
		/* z - axis - blue */
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,len);
	glEnd();
	/* setting line width back to normal, 
	 * cause it wont be done automatically 
	 * after ending this scope */ 
	glLineWidth(DEFAULT_LINE_WIDTH);
    glEnable(GL_LIGHTING);

}
void draw_helper(){
	if(animation_helper){
		draw_coord(HELPER_SIZE);
		draw_plane(HELPER_SIZE);
	}
}