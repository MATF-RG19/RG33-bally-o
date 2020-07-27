#ifndef COLLISION_H
#define COLLISION_H

#include "settings.h"
#include "player.h"
#include "map.h"

#define COLLISION_FLOOR (600.0f)


int player_floor_collision(player *p);
void player_floor_collision_event(player *p);
int player_brick_collision(player *p, map *m);
void player_brick_collision_event(player *p, map *m);
void collision_checks(player *p, map *m);

#endif
