#ifndef HELPER_H
#define HELPER_H

#include <GL/glut.h>

#define DEFAULT_LINE_WIDTH (1)
#define AXIS_LINE_WIDTH (3)
#define HELPER_SIZE (5000000)


extern int animation_helper;
extern const float m_pi;
extern const float m_eps;


void error_msg(const char *s);
void draw_coord(float len);
void set_normal_and_vertex(float u, float v, float r);
void draw_sphere(float r);
void draw_cube(GLfloat center_pos_x, GLfloat center_pos_y, GLfloat center_pos_z, GLfloat edge_length);
void draw_plane(float len);
void draw_helper();
void draw_pane();
void toggle_helper();


#endif
