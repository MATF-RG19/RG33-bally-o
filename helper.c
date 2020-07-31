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
int keys[256];

void error_msg(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void set_normal_and_vertex(float u, float v, float r)
{
	glNormal3f(sin(u) * sin(v) * r, cos(u) * r, sin(u) * cos(v) * r);
	glVertex3f(sin(u) * sin(v) * r, cos(u) * r, sin(u) * cos(v) * r);
}

/* possibly will be switched with something else */
void draw_sphere(float r)
{
	glPushMatrix();
		for(float u = 0.0f; u < m_pi; u += m_pi / 20.0f){
			glBegin(GL_TRIANGLE_STRIP);
				for(float v = 0.0f; v <= m_pi*2 + m_eps; v += m_pi/ 20.0f){
					set_normal_and_vertex(u, v, r);
					set_normal_and_vertex(u + m_pi / 20.0f, v, r);
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

/* used code from https://www.youtube.com/watch?v=vcMox6i8f4Y */
void draw_cube( GLfloat center_pos_x, GLfloat center_pos_y, GLfloat center_pos_z, GLfloat edge_length )
{
    GLfloat half_side_length = edge_length * 0.5f;
    
    GLfloat vertices[] =
    {	// front face
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // top left
        center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // top right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length, // bottom right
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length, // bottom left
        // back face
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // top left
        center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // top right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // bottom right
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // bottom left
        // left face
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // top left
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // top right
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // bottom right
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length, // bottom left
        // right face
        center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // top left
        center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // top right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // bottom right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length, // bottom left
        // top face
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // top left
        center_pos_x - half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // top right
        center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z - half_side_length, // bottom right
    	center_pos_x + half_side_length, center_pos_y + half_side_length, center_pos_z + half_side_length, // bottom left
        // top face
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length, // top left
        center_pos_x - half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // top right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z - half_side_length, // bottom right
        center_pos_x + half_side_length, center_pos_y - half_side_length, center_pos_z + half_side_length  // bottom left
    };
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
	glShadeModel(GL_SMOOTH);
	
	glDrawArrays(GL_QUADS, 0, 24 );
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_pane()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glColor3f(0,1,0);
		glBegin(GL_POLYGON);
			glVertex3f(100,0, 0);
			glVertex3f(0,100, 0);
			glVertex3f(-100,0,0);
			glVertex3f(0,-100,0);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);


}

void toggle_helper()
{
	animation_helper = !animation_helper ? 1:0; 
}

void print_keys()
{
	fprintf(stdout, "Keys active/inactive: W: %d A: %d S: %d D: %d R: %d Q: %d\n", keys['w'], keys['a'], keys['s'], keys['d'], keys['r'], keys['q']);
}
