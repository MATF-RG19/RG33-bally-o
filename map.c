#include "map.h"
#include <GL/glut.h>
#include <time.h>
#include <assert.h>
#include "helper.h"

void draw_tile(tile *t)
{
    glPushMatrix();
		GLfloat ambient1[] = {1.0,0,0,0};
    	GLfloat diffuse1[] = {1.0,1,1,0};
    	GLfloat specular1[] = {1,0.6,1.0,1};
    	GLfloat shininess1 = 80;

    	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
		glScalef(t->scaling_factor, 1, 1);
		draw_cube(t->x,t->y,0, t->edge_length);

	glPopMatrix();
}




void init_map(map *m)
{
    m->capacity = 1000;
    m->current_size = 500;
    m->t = (tile*) malloc(m->current_size * sizeof(tile));
    assert(m->t != NULL);

    /* set seed */
    srand(time(NULL));
    for(int i = 0; i < m->current_size; i++){
        m->t[i].x = 50 * (i+1);
        m->t[i].y = (float) rand_range(LIMIT_Y, -LIMIT_Y);
        m->t[i].edge_length = EDGE_LENGTH_START;
        m->t[i].scaling_factor = SCALING_FACTOR_START;
    }

}
void draw_map(map *m)
{
    glPushMatrix();
        for(int i = 0; i < m->current_size; i++)
            draw_tile(&m->t[i]);
    glPopMatrix();

}
