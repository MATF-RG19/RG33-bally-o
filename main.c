#include <GL/glut.h>
#include <stdlib.h>
#include "helper.h"
#include "player.h"
#include "settings.h"
#include "map.h"
#include <stdio.h>
#include "collision.h"

static player p;
static animation_settings as; 
static map m;
static const char *name = "bally-o";

// static float camera_parameter = 0; /* deprecated code */
/* callback functions */
static void on_display(void);
static void on_reshape(int, int);
static void on_keyboard(unsigned char, int, int);
static void on_keyboard_up(unsigned char, int, int);
static void on_timer(int);

void init_params(void);
void init_light(void);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(START_WINDOW_WIDTH_SIZE, START_WINDOW_HEIGHT_SIZE);
	glutInitWindowPosition(START_WINDOW_POS_X, START_WINDOW_POS_Y);
	glutCreateWindow(name);

	/* init callback functions */
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	glutKeyboardUpFunc(on_keyboard_up);
	/* use current time as seed for random number generator */
	init_params();

	glutMainLoop();

	return 0;
}

void init_params()
{
	init_player(&p);
	init_animation_settings(&as);
	init_map(&m);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	init_light();
	
	tile tmp = get_closest_to_center(&m);
	p.x_curr = tmp.x;
	p.y_curr = tmp.y + tmp.edge_length / 2.0 + p.r;

	glClearColor(0.0,0.5,0.5,0);
	glClearDepth(1500.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void init_light(void)
{
	/* light coeffs */ 
	GLfloat light_position[] = { 1, 1, 1, 0 };
	GLfloat light_ambient[] = { 0.7, 0.4, 0.3, 1 };
	GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
	GLfloat light_specular[] = { 0.3, 0.4, 0.9, 1 };
	
	/* set up a light model */ 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glShadeModel(GL_SMOOTH);
}
static void on_keyboard_up(unsigned char key, int x, int y)
{
	switch(key){
		case 'q':
			keys['q'] = 0;
			break;
		case 'd':
			keys['d'] = 0;
			if(collision_tile_flag){
				p.player_state = ROLLING_RIGHT;
			}
			else{
				p.player_state = FALLING;
			}
			break;
		case 'a':
			keys['a'] = 0;
			if(collision_tile_flag){
				p.player_state = ROLLING_LEFT;
			}
			else{
				p.player_state = FALLING;
			}
			break;
		case 'w':
			keys['w'] = 0;
			p.player_state = FALLING;
			break;
		case 'p':
			keys['p'] = 0;
			break;
	}
}
/* callback function that registers keyboard events */
static void on_keyboard(unsigned char key, int x, int y)
{
	switch(key){
		case 27:
			quit_game();
			break; /* will never get here */
		case 'p':
			keys['p'] = 1;
			if(!as.animation_active){
				glutTimerFunc(timer_msec_interval, on_timer, timer_id);
				resume_game(&as);
			}
			break;
		case 'q':
			keys['q'] = 1;
			pause_game(&as);
			glutPostRedisplay();
			break;
		case 'r':
			keys['r'] = 1;
			/* restart animation */
			restart_game(&p, &as);
			glutPostRedisplay();
			break;
		case 'w':
			keys['w'] = 1;
			p.player_state = JUMPING;
			break;
		case 'd':
			keys['d'] = 1;
			p.player_state = ROLLING_RIGHT;

			break;
		case 'a':
			keys['a'] = 1;
			p.player_state = ROLLING_LEFT;
			break;
		case 's':
			keys['s'] = 1;
			break;
	}
}

static void on_timer(int id)
{
	if(timer_id != id)
		return;

	if(p.player_state == DEATH)
	{
		as.animation_active = 0;
	}


	move_left(&p);
	move_right(&p);
	jump(&p);
	death(&p);
	player_brick_collision_event(&p, &m);
	
	glutPostRedisplay();
	
	if(as.animation_active)
		glutTimerFunc(timer_msec_interval, on_timer, timer_id);
}

static void on_reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(CAMERA_ANGLE, width / (float) height, Z_NEAR, Z_FAR);
}

static void on_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* setting up camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(p.x_curr, 0, Z_CAMERA_EYE, p.x_curr, 0, 0, 0, 1, 0);

	draw_ball(&p);
	draw_map(&m);

	print_game_status_info(&p, &as);
	print_keys();
	glutSwapBuffers();
}



