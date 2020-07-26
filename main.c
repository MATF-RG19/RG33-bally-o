#include <stdio.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"
/* prebaceno u helper.h */
/* define macros for magic numbers */ 
#define MSEC_IN_SEC (1000)
#define MSEC_TO_SEC(x) ((x)/(MSEC_IN_SEC))

#define Z_CAMERA_EYE (1500)
#define Z_NEAR (1)
#define Z_FAR  (2000)
#define CAMERA_ANGLE (60)

/* animation parameters */
static const int timer_id  = 1; 
static const int timer_msec_interval = 20;
static int animation_active;
static float animation_parameter;

/* physics and maths */ 
static const float g_y = 9.81f;

/* structure for ball */ 
static float x_curr; //player.h
static float y_curr; //player.h
static float v_x; //player.h
static float v_y; //player.h
static float r = 50.0f; //player.h
static int jump_state; //player.h
static int jump_count; //player.h

/* callback functions */
static void on_display(void);
static void on_reshape(int, int);
static void on_keyboard(unsigned char, int, int);
static void on_timer(int);

/* init parameters and helper functions */
void init_params(void);
/* draw objects */
void draw_platform(float x, float y); //map.h
void draw_ball(float r, float x, float y, float animation_parameter); //player.h






void restart_animation(int animation_active, float animation_parameter, int animation_helper); //settings.h
void restart_game(float x, float y, float v_x, float v_y, int jump_state, int jump_count); //settings.h
void stop(float v_x, float v_y, int jump_state, float animation_parameter, int animation_active); //settings.h


/* collision stuff */
/* todo exchange parameters with a struct */
int player_floor_collision(float x, float y, float r);
void player_floor_collision_event(float x, float y, float r);
int player_brick_collision(float x, float y, float r, float d);
void player_brick_collision_event(float x, float y, float r, float d);

//void print_game_status_info(float x_curr, float y_curr, float animation_parameter, int animation_active);
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("bally-o");
	
	/* init callback functions */
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	
	init_params();

	glutMainLoop();



	return 0;
}

void init_params(){
	animation_active = 0;
	animation_parameter = 0;
	animation_helper = 0;
	v_x = 10;
	v_y = 3;
	x_curr = 50;
	y_curr = 300;
	jump_state = 0;
	jump_count = 2;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	/* light coeffs */ 
	GLfloat light_position[] = { 1, 1, 1, 0 };
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
	GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
	/* set up a light model */ 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glClearColor(0,0,0,0);
	glClearDepth(1.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void draw_ball(float r, float x, float y, float animation_parameter)
{
	glPushMatrix();
		glTranslatef(x_curr, y_curr, 0);
		glRotatef(animation_parameter, 0, 0, -1);
		glColor3f(1,0,0);
		glScalef(r,r,r);
		draw_sphere();
	glPopMatrix();
}

// void print_game_status_info(float x_curr, float y_curr, float animation_parameter, int animation_active)
// {
// 	fprintf(stdout, "*************************************************************************\n");
// 	fprintf(stdout, "Information:\nBall (Player) at place (x: %f, y: %f, z: 1500).\n", x_curr, y_curr);
// 	fprintf(stdout, "Distance from ground: (%f).\nAnimation status: %d\nAnimation parameter: (%f) \n", (y_curr), animation_active, animation_parameter);
// 	/* create a specific check collision detection function for this */ 
// 	if(player_floor_collision(x_curr, y_curr, r)){
// 		fprintf(stdout, "*************************************************************************\n");
// 		fprintf(stdout, "Collision detected with floor: you lost!\n");
// 		fprintf(stdout, "*************************************************************************\n");

// 	}
// 	fprintf(stdout, "*************************************************************************\n");

// }

static void on_keyboard(unsigned char key, int x, int y)
{
	switch(key){
		case 27:
			exit(EXIT_SUCCESS);
			break;
		case 's':
		case 'S':
			if(!animation_active){
				glutTimerFunc(timer_msec_interval, on_timer, timer_id);
				animation_active = 1;
			}
			break;
		case 'q':
		case 'Q':
			animation_active=0;
			break;
		case 'r':
		case 'R':
			/* restart animation */
			restart_game(x_curr, y_curr, v_x, v_y, jump_state, jump_count);
			restart_animation(animation_active, animation_parameter, animation_helper);
			glutPostRedisplay();
			break;
		case 'w':
		case 'W':
			animation_parameter+=6;
			v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
			x_curr += v_x;
			v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
			y_curr += 20*v_y;
			glutPostRedisplay();
			/* jump animation */
			break;
		case 'd':
		case 'D':
			animation_parameter+=6;
			v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
			x_curr += v_x;
			v_y += g_y * MSEC_TO_SEC(timer_msec_interval)/ 2;
			y_curr -= v_y;
			if(player_floor_collision(x_curr, y_curr, r)){
				/* stop the animation if it falls under */
				player_floor_collision_event(x_curr, y_curr, r);
			}
			glutPostRedisplay();

			break;
		case 'h':
		case 'H':
			/* toggle xz pane and catestrian system */
			animation_helper = !animation_helper ? 1:0; 
			glutPostRedisplay();
			break;
	}
}

static void on_timer(int id)
{
	if(timer_id != id)
		return;

	animation_parameter+=6;
	v_x += g_y * MSEC_TO_SEC(timer_msec_interval) / 2;
	x_curr += v_x;
	v_y += g_y * 	MSEC_TO_SEC(timer_msec_interval)/ 2;
	y_curr -= v_y;
	if(player_floor_collision(x_curr, y_curr, r)){
		/* stop the animation if it falls under */
		player_floor_collision_event(x_curr, y_curr, r);
	}
	glutPostRedisplay();
	if(animation_active)
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
	gluLookAt(x_curr, 1, Z_CAMERA_EYE, x_curr, 0, 0, 0, 1, 0);
	/* this will go to a function draw_ball */ 
	if(animation_helper){
		draw_coord(HELPER_SIZE);
		draw_plane(HELPER_SIZE);
	}

	GLfloat ambient[] = {0.3,0.3,0.3,0};
  	GLfloat diffuse[] = {0,0.7,0,0};
  	GLfloat specular[] = {0.6,0.6,0.6,0};
  	GLfloat shininess = 80;

  	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


	/* y coord will always be the distance between our ball and the ground */
	//print_game_status_info(x_curr, y_curr, animation_parameter, animation_active);
	draw_ball(r, x_curr, y_curr, animation_parameter);
	draw_platform(55.0,65.0);
	glutSwapBuffers();
}

void restart_animation(int animation_active, float animation_parameter, int animation_helper)
{
	animation_active = 0;
	animation_parameter = 0.0;
	animation_helper = 0;
}
/* create a structure player that will do this work */
void restart_game(float x, float y, float v_x, float v_y, int jump_state, int jump_count)
{
	v_x = 10;
	v_y = 5;
	x_curr = 50;
	y_curr = 300;
	jump_state = 0;
	jump_count = 2;

}
int player_floor_collision(float x, float y, float r)
{
	/* just comparing y coord with r if it colides, return it to r */
	return (y <= r) ? 1 : 0;
}

void player_floor_collision_event(float x, float y, float r)
{
	if(player_floor_collision(x,y,r)){
		y = r;
		animation_active = 0;
		x = 0;
		v_x = 0;
		v_y = 0;

	}

}

void draw_platform(float x, float y)
{

	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(x,y,0);
		glColor3f(0.0f,1.0f,0.0f);
		glScalef(200,100,1);
		glutWireCube(1);
	glPopMatrix();
	fprintf(stdout, "iscrtana kocka");
	glEnable(GL_LIGHTING);
}

void stop(float v_x, float v_y, int jump_state, float animation_parameter, int animation_active)
{
	v_x = 0;
	v_y = 0;
	jump_state = 0;
	animation_parameter = 0;
	animation_active = 0;

}
