#ifndef MAP_H
#define MAP_H

#define MAX_SIZE (10000)
#define SIZE (500)
#define LIMIT_Y (600)
#define SCALING_FACTOR_START (10)
#define EDGE_LENGTH_START (50)
/* random range generated macro */
#define rand_range(a,b) (rand() % ((a) - (b) + 1)) + (b)





typedef struct tile{
    float x, y;
    float edge_length;
    float scaling_factor;
}tile;
typedef struct map{
    unsigned int capacity;
    unsigned int current_size;
    tile *t; /*array of tiles */
}map;


int cmp_func(const void *a, const void *b);
tile get_closest_to_center(map *m);


void init_tile(tile *t);
void init_map(map *m);
void add_tile_to_map(map **m, tile t);
void draw_tile(tile *t);
void draw_map(map *m);
float eucledean_dist(float x1, float y1);
void destroy_map(map *m);
void print_map_coords(map *m);

#endif