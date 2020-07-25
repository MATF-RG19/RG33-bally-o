// #include <GL/glut.h>
// #include "helper.h"


// void set_normal_and_vertex(float u, float v)
// {
// 	glNormal3f(sin(u) * sin(v), cos(u), sin(u) * cos(v));
// 	glVertex3f(sin(u) * sin(v), cos(u), sin(u) * cos(v));
// }

// void draw_sphere()
// {
// 	glPushMatrix();
// 		for(float u = 0.0f; u < m_pi; u += m_pi / 20.0f){
// 			glBegin(GL_TRIANGLE_STRIP);
// 				for(float v = 0.0f; v <= m_pi*2 + m_eps; v += m_pi/ 20.0f){
// 					set_normal_and_vertex(u, v);
// 					set_normal_and_vertex(u + m_pi / 20.0f, v);
// 				}
// 			glEnd();
// 		}
// 	glPopMatrix();
// }

// void draw_plane(float len)
// {
// 	glColor3f(0.75,0.75,0.75);
// 	glBegin(GL_POLYGON);
// 		glVertex3f(len, 0, 0);
// 		glVertex3f(-len, 0, 0);
// 		glVertex3f(0, 0, -len);
// 		glVertex3f(0, 0, len);
// 	glEnd();

// }

// void draw_coord(float len)
// {
// 	glLineWidth(DEFAULT_LINE_WIDTH);
//  	glBegin(GL_LINES);
// 		/* x - axis - red */ 
//   	glColor3f(1,0,0);
//   	glVertex3f(0,0,0);
//   	glVertex3f(len,0,0);
// 		/* y - axis - green */
//   	glColor3f(0,1,0);
//   	glVertex3f(0,0,0);
//   	glVertex3f(0,len,0);
// 		/* z - axis - blue */
//   	glColor3f(0,0,1);
//   	glVertex3f(0,0,0);
//   	glVertex3f(0,0,len);
// 	glEnd();
// 	/* setting line width back to normal, 
// 	 * cause it wont be done automatically 
// 	 * after ending this scope */ 
// 	glLineWidth(DEFAULT_LINE_WIDTH);
// }