#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "map.h"


int player_floor_collision(player *p);
void player_floor_collision_event(player *p);
int player_brick_collision(player *p, map *m);
void player_brick_collision_event(player *p, map *m);
void collision_checks(player *p, map *m);

#endif
