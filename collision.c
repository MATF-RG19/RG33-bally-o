#include "collision.h"
#include <stdio.h>

int player_floor_collision(player *p)
{
    return p->y_curr - p->r <= COLLISION_FLOOR;
}

void player_floor_collision_event(player *p)
{
    /* add some better info output */
    printf("Desila se kolizija sa podom.\n");
    if(player_floor_collision(p)){
        /* stop the ball*/
        p->v_x = 0;
        p->v_y = 0;
        p->player_state = DEATH; /* nakon toga je izgubljeno */
    }
}

int brick_collision_half_edge1(player *p, tile *t)
{
    return (p->y_curr - p->r < t->y + (t->edge_length / 2.0f));
}
int brick_collision_half_edge2(player *p, tile *t)
{
    return (p->x_curr - p->r < (t->edge_length * t->scaling_factor) / 2.0f && p->y_curr - p->r < (t->edge_length * t->scaling_factor) / 2.0f); 
}


/* rastojanje samo izmedju polovine dijagonale i polovine sranice */
int player_tile_collision(player *p, tile *t)
{
    return brick_collision_half_edge1(p, t) || brick_collision_half_edge2(p, t);
}
void player_brick_collision_event(player *p, map *m)
{
    for(int i = 0; i < m->current_size; i++){
        if(brick_collision_half_edge1(p, &m->t[i])){
            p->x_curr = m->t[i].x + (m->t[i].edge_length) / 2.0f;
            p->y_curr = m->t[i].y + (m->t[i].edge_length) / 2.0f;
            p->v_y += 0;
        }
        else if(brick_collision_half_edge2(p, &m->t[i])){
            p->x_curr = m->t[i].x - (m->t[i].edge_length * m->t[i].scaling_factor) / 2.0f;
            p->y_curr = m->t[i].y - (m->t[i].edge_length * m->t[i].scaling_factor) / 2.0f;
            p->v_y += 0;

        }
    }
}

void collision_checks(player *p, map *m)
{
    player_brick_collision_event(p,m);
    player_floor_collision_event(p);
}


void print_collision_info(player *p, map *m)
{
    fprintf(stdout, "*************************************************\n");
    fprintf(stdout, "Collision infomration:\n");
    fprintf(stdout, "Player (%f, %f)\n", p->x_curr, p->y_curr);
    fprintf(stdout, "Collision with floor: %d\n", player_floor_collision(p));
    fprintf(stdout, "*************************************************\n");
}