#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "graphics.h"

Emitter *e;
Obstacle *o;
Wind *w;

// Function for drawing the contents of the screen
void display(void) {
  //printf("Entering display\n");
  GLfloat position[] = {10.0, 5.0, 20.0, 1.0};
  int i;
  // clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor4f(1.0, 1.0, 1.0, 0.5);
  
  // reset the modelview matrix
  glLoadIdentity();
  
  // set up the viewing transformation
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  // set up the light
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  
  // set up a sphere
  //glutSolidSphere(1.0, 32, 32);
  
  //printf("Before emit stuff\n");
  emitter_update(e, o, w);
  emitter_draw(e);
  obstacle_draw(o);
  // draw everything
  glFlush();
  usleep(10000);
  glutPostRedisplay();

}

//  Function called when the window is resized
void reshape(int w, int h) {
	// set the viewport to the updated window size
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// move to projection matrix mode
  glMatrixMode(GL_PROJECTION);

	// reset the projection to identity
  glLoadIdentity();

	// create the new perspective matrix
  gluPerspective((GLdouble)30, (GLdouble)w / (GLdouble)h, (GLdouble)2, (GLdouble)100);

	// go back to model view matrix mode
  glMatrixMode(GL_MODELVIEW);

	// reset the modeview matrix
  glLoadIdentity();
}

// init function
void init(void) {
  float loc[3] = {0.0, 0.0, 0.0};
  float coord[6] = { -0.05, 0.05, 0.3, 0.3, -0.05, 0.05 };
    float speed[3] = {0.003, 0, 0.0};//{0.2,0.0,0.3};
    float wloc[3] = {2.0, 0.0, 0.0};//{0.05,0.2,0};
  // background color
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // whether shading is smooth or flat
  glShadeModel(GL_SMOOTH);

  //initlights();
  //printf("Before seg?\n");
  e = emitter_create();
  o = obstacle_create();
  w = wind_create();
  emitter_set(e, loc, 500000);
  obstacle_set(o, coord, 0, 0 );
  wind_set(w, wloc,speed);
  glEnable(GL_DEPTH_TEST);
  //printf("After seg?\n");
}

//  This function is called whenever a key event occurs.
//  The key value is in "key" and "x" and "y" hold the current mouse position
void keyboard(unsigned char key, int x, int y)
{
   switch( key) {
   case 'q': // quit
     emitter_free(e);
     obstacle_free(o);
     wind_free(w);
     exit(0);
     break;
   default:
     break;
   }
}

// main function
int main(int argc, char **argv) {

  // initialize
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sphere");
  init();

  // set up the callback functions
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  // run the main loop
  glutMainLoop();

  return(0);
}
