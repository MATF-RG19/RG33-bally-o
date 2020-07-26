#ifndef PLAYER_H
#define PLAYER_H

/* representing player states for jumping and collision functions */
typedef enum _game_state{
    ROLLING = 1,  /* you are rolling if you are on solid ground */
    JUMPING = 2,  /* you are in jumping mode if you jump/double jump */
    FALLING = 3,  /* you are falling after the jump ends, if you didnt double jump, you can jump now */
    DEATH   = 4   /* you colided with the floor */
}game_state;

typedef struct _player{
    float r; /* player's radius*/
    float x_curr; /* current x position of our object centre */
    float y_curr; /* current y position of our object centre */
    float v_x;    /* speed vector for x axis */
    float v_y;    /* speed vector for y axis */ 
    int jump_counter; /* you can only jump twice, but then you need to fall on the ground to replenish your counter */
    game_state player_state; /* current state of our player */

}player;



player* init_player(float r, 
                    float x_curr, 
                    float y_curr, 
                    float v_x, 
                    float v_y,
                    int jump_counter,
                    game_state player_state);
//void player_destroy(player* p);
void draw_ball(float r, float x, float y, float animation_parameter); 
void jump(void);
 


#endif