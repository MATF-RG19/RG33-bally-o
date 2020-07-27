#include <GL/glut.h>
#include <stdlib.h>
#include "helper.h"
#include "player.h"
#include "settings.h"
#include "map.h"

static player p;
static animation_settings as; 
static map m;
static const char *name = "bally-o";

/* callback functions */
static void on_display(void);
static void on_reshape(int, int);
static void on_keyboard(unsigned char, int, int);
static void on_timer(int);

/* init parameters  */
void init_params(void);
void init_light(void);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(name);

	/* init callback functions */
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
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

	glClearColor(0,0,0,0);
	glClearDepth(1.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void init_light(void)
{
	/* light coeffs */ 
	GLfloat light_position[] = { 1, 1, 1, 0 };
	GLfloat light_ambient[] = { 0.5, 0.4, 0.3, 1 };
	GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
	GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
	
	/* set up a light model */ 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glShadeModel(GL_SMOOTH);
}

static void on_keyboard(unsigned char key, int x, int y)
{
	switch(key){
		case 27:
			quit_game();
			break; /* will never get here */
		case 's':
		case 'S':
			if(!as.animation_active){
				glutTimerFunc(timer_msec_interval, on_timer, timer_id);
				resume_game(&as);
			}
			break;
		case 'q':
		case 'Q':
			pause_game(&as);
			glutPostRedisplay();
			break;
		case 'r':
		case 'R':
			/* restart animation */
			restart_game(&p, &as);
			glutPostRedisplay();
			break;
		case 'w':
		case 'W':
			p.player_state = JUMPING;
			glutPostRedisplay();
			break;
		/* probably will be deleted */
		case 'd':
		case 'D':
			move_right(&p);
			glutPostRedisplay();
			break;
		case 'a':
		case 'A':
			move_left(&p);
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

	move_right(&p);
	jump(&p);

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
	gluLookAt(p.x_curr, 0, 1500, p.x_curr, 0, 0, 0, 1, 0);
	/* this will go to a function draw_ball */ 
	
	draw_helper();
	/* y coord will always be the distance between our ball and the ground */
	//print_game_status_info(x_curr, y_curr, animation_parameter, animation_active);
	draw_ball(&p);
	draw_map(&m);

	glutSwapBuffers();
}

