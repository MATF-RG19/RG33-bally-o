#ifndef PLAYER_H
#define PLAYER_H


#define MSEC_IN_SEC (1000)
#define MSEC_TO_SEC(x) ((x)/(MSEC_IN_SEC))


extern const float g_y;
extern const int timer_id;
extern const int timer_msec_interval;

/* representing player states for jumping and collision functions */
typedef enum _game_state{
    ROLLING_RIGHT = 0,
    ROLLING_LEFT = 1,  /* you are rolling if you are on solid ground */
    JUMPING = 2,  /* you are in jumping mode if you jump/double jump */
    FALLING = 3,  /* you are falling after the jump ends, if you didnt double jump, you can jump now */
    DEATH   = 4,   /* you colided with the floor */
    STILL   = 5,
}game_state;

typedef struct _player{
    float r; /* player's radius*/
    float x_curr; /* current x position of our object centre */
    float y_curr; /* current y position of our object centre */
    float v_x;    /* speed vector for x axis */
    float v_y;    /* speed vector for y axis */ 
    float jump_height;
    game_state player_state; /* current state of our player */
    float animation_parameter; /* animation_parameter, used for rotation of the ball */

}player;



void init_player(player *p);
void draw_ball(player *p); 
void move_left(player *p);
void move_right(player *p);
void jump(player *p);
void jump_special_1(player *p);
void jump_special_2(player *p);
void still(player *p);
void death(player *p);
const char* get_player_state(player *p);



#endif
