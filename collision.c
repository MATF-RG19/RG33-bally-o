#include "collision.h"
#include <stdio.h>


int collision_tile_flag = 0;

int player_floor_collision(player *p)
{
    return p->y_curr - p->r <= COLLISION_FLOOR;
}

void player_floor_collision_event(player *p)
{
    /* add some better info output */
    if(player_floor_collision(p)){
        /* stop the ball*/
        p->v_x = 0;
        p->v_y = 0;
        p->player_state = DEATH; /* nakon toga je izgubljeno */
    }
}

int collision_tile(player *p, tile *t)
{
    return p->x_curr < t->x + t->edge_length &&
           p->x_curr + p->r > t->x &&
           p->y_curr < t->y + t->edge_length &&
           p->y_curr + p->r > t->y;
}


void player_brick_collision_event(player *p, map *m)
{
    for(int i = 0; i < m->current_size; i++){
        tile tmp = m->t[i];
        if(collision_tile(p, &tmp)){
            p->x_curr = tmp.x;
            p->y_curr = tmp.y + tmp.edge_length / 2.0f  + p->r + 5.0f;
            p->jump_height = p->y_curr + 100.0f;
            collision_tile_flag = 1;
        }
        else{
            collision_tile_flag = 0;
        }
    }
}

