#ifndef MAP_H
#define MAP_H

#define SIZE (800)
#define INC (50)
#define LIMIT_Y (500)
#define EDGE_LENGTH_START (50.0f)
#define HEIGHT_Y (100)
/* random range generated macro */
#define rand_range(a,b) (rand() % ((a) - (b) + 1)) + (b)



typedef struct tile{
    float x, y;
    float edge_length;
}tile;
typedef struct map{
    unsigned int current_size;
    tile *t; /*array of tiles */
}map;

int cmp_fu(map *m);
void init_tile(tile *t);
void init_map(map *m);
void draw_tile(tile *t);
void draw_map(map *m);
float eucledean_dist(float x1, float y1);
tile get_closest_to_center(map *m);

#endif