#ifndef RENDER_H
#define RENDER_H

#include "helper.h"
#include "player.h"


/* render stuff that use postredisplay */

void render_player(void (*f)(player *p));
void render_animation(void (*f)(player *p));





#endif