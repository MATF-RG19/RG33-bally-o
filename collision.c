#include "collision.h"


int player_floor_collision(player *p)
{
    return (p->y_curr <= p->r) ? 1 : 0;
}
void player_floor_collision_event(player *p)
{
    if(player_floor_collision(p)){
        p->y_curr = r;
        as->animation_active = 0;
        p->v_x = 0;
        p->v_y = 0;
    }
}

int player_brick_collision(player *p, map *m);
void player_brick_collision_event(player *p, map *m);