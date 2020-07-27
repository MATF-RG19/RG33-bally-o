#include "collision.h"
#include <stdio.h>

int player_floor_collision(player *p)
{
    return (p->y_curr - p->r <= (COLLISION_FLOOR)) ? 1 : 0;
}
void player_floor_collision_event(player *p)
{
    /* add some better info output */
    printf("Desila se kolizija sa podom.\n");
    if(player_floor_collision(p)){
        p->v_x = 0;
        p->v_y = 0;
    }
}

//int player_brick_collision(player *p, map *m);
// void player_brick_collision_event(player *p, map *m);