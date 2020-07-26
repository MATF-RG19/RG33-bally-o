#ifndef HELPER_H
#define HELPER_H


#define DEFAULT_LINE_WIDTH (1)
#define AXIS_LINE_WIDTH (3)
#define HELPER_SIZE (5000000)


extern int animation_helper;
extern const float m_pi;
extern const float m_eps;

// typedef struct _helper{
//     int animation_helper;
// }helper;



//todo: add a structre maybeeeee */
//helper* init_helper();
void draw_coord(float len);
void set_normal_and_vertex(float u, float v);
void draw_sphere(void);
void draw_plane(float len);


#endif