#ifndef MAP_H
#define MAP_H

#define MAX_SIZE (1000)
#define SIZE (500)

typedef struct map{
    unsigned int max_size;
    unsigned int size;
    tile *t; /*array of tiles */
}map;


typedef struct tile{
    float x, y;
    float scaling_factor;
}tile;


void init_tile(tile *t);
void init_map(map *m);
void draw_tile(tile *t);
void draw_map(map *m);
void destroy_map(map *m);
void map_status_info(map *m);

#endif