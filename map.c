#include "map.h"
#include <GL/glut.h>
#include <time.h>
#include <assert.h>
#include "helper.h"
#include <stdio.h>
#include <math.h>

void draw_tile(tile *t)
{
    glPushMatrix();
		GLfloat ambient1[] = {1.0,1.0,0,0};
    	GLfloat diffuse1[] = {1.0,1,1,0};
    	GLfloat specular1[] = {1,0.6,1.0,1};
    	GLfloat shininess1 = 80;

    	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
		draw_cube(t->x,t->y,0, t->edge_length);

	glPopMatrix();
}

void init_map(map *m)
{
    m->current_size = SIZE;
    m->t = (tile*) malloc(m->current_size * sizeof(tile));
    assert(m->t != NULL);
    
    /* set seed */
    srand(time(NULL));
    float height = (float) rand_range(LIMIT_Y, -LIMIT_Y);
    
    for(int i = 0, r = 0; i < m->current_size; i++, r++){
        m->t[i].x = INC * (i+1); 
        m->t[i].y = height;
        m->t[i].edge_length = EDGE_LENGTH_START;
        if(r > 5){
            if(rand() % 2 == 1){
                height += (float) (rand() % HEIGHT_Y) + HEIGHT_Y;
                if(height > LIMIT_Y)
                    height = LIMIT_Y;
            }
            else{
                height -= (float) (rand() % HEIGHT_Y) + HEIGHT_Y;
                if(height < -LIMIT_Y)
                    height = -LIMIT_Y;
            }
            r = 0;
        }
    }
    

}

void draw_map(map *m)
{
    glPushMatrix();
        for(int i = 0; i < m->current_size; i++)
            draw_tile(&m->t[i]);
    glPopMatrix();

}

int cmp_func(const void *a, const void *b)
{
    tile tmp1, tmp2;
    tmp1 = *(tile*)a;
    tmp2 = *(tile*)b;
    return eucledean_dist(tmp1.x, tmp1.y) > eucledean_dist(tmp2.x, tmp2.y);
}

tile get_closest_to_center(map *m)
{
    qsort(m->t, m->current_size, sizeof(tile), cmp_func);
    return m->t[0];
}

float eucledean_dist(float x1, float y1)
{
    return sqrt(x1*x1 + y1*y1);
}

