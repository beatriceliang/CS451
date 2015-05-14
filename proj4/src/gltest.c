/* Beatrice Liang and Jenny Lin 
   Spring 2015 

   Drawing unit testing */

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "graphics.h"

double angle = 0.0;
double posx = 30.0;
double posz = 30.0;
double eyeAngle = 0.0;

Building *b;

void sim_setup( void ){
  b = building_new();
  building_init( b, 10, 10, 17, 1 );
  building_partition( b );
}

void shape_draw( Shape *s ){
  if( strcmp(s->symbol, "WALL") == 0 ){
    glBegin(GL_QUADS);
    glNormal3d( s->dir[0], s->dir[1], s->dir[2]);
    /*
    glColor4f( (float)(s->rc[0])/(float)(b->rows), 
	       (float)(s->rc[1])/(float)(b->cols),
	       (float)(s->floor)/(float)(b->floors), 1.0f );
    */
    //front facing
    if(s->dir[2] == 1 ){
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
    }
    //back facing
    if(s->dir[2] == -1 ){
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
      }
    //left facing 
    if(s->dir[0] == -1){
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]);
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
    }
    //right facing
    if(s->dir[0] == 1){
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
    }
    //upward facing
    if(s->dir[1] == 1){
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
    }
    //downward facing
    if(s->dir[1] == -1){
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]);
      glVertex3f(s->xyz[0]+s->wdh[0], s->xyz[1]+s->wdh[2], s->xyz[2]-s->wdh[1]);
      glVertex3f(s->xyz[0], s->xyz[1], s->xyz[2]-s->wdh[1]);
    }
    glEnd();
  }
  else{
    //Numbers are BAD!!!
    /*
    glPushMatrix();
    glTranslatef( s->wdh[0]/2.0, s->xyz[1]+(s->wdh[2]/2), -s->wdh[1]/2.0);
    glScalef(s->wdh[0], s->wdh[2], s->wdh[1]);
    glutSolidCube(1);
    glPopMatrix(); 
    */
    return;
  }
}

void draw_building( void ){
  Shape *s;
  s = ll_head( b->design );

  while( s ){
    //printf("%s \n", s->symbol);
    glColor4f( s->xyz[0]/10.0, 
	       s->xyz[1]/17.0,
	       -s->xyz[2]/10.0, 1.0f );

    shape_draw( s );

    s = ll_next( b->design );
  }
}

// Function for drawing the contents of the screen
void display(void) {
    
    GLfloat position[] = {20.0, 30.0, 40.0, 1.0};
    Shape *s;
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    
    // reset the modelview matrix
    glLoadIdentity();
    
    // set up the viewing transformation
    /*gluLookAt(posx, 10.0, posz, 
	    posx+8.0*sin(angle*M_PI/180.0), 
	    5.0+(4*sin(eyeAngle*M_PI/180.0)), 
	    posz+8.0*cos(angle*M_PI/180.0), 
	    0.0, 1.0, 0.0); 
    */
    gluLookAt((posx*sin(angle*M_PI/180.0))+5, 
	      8.0+(8*sin(eyeAngle*M_PI/180.0)), 
	      (posz*cos(angle*M_PI/180.0))-5, 
	      5.0, 8.0, -5.0, 0.0, 1.0, 0.0); 
	      
    //gluLookAt(0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set up the light
    glLightfv(GL_LIGHT0, GL_POSITION, position);
 
    draw_building();
    s = ll_head( b->design );
    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
    glPushMatrix();
    glTranslatef( s->wdh[0]/2.0, 16.5, -s->wdh[1]/2.0);
    glScalef(s->wdh[0], s->wdh[2], s->wdh[1]);
    glutSolidCube(1);
    glPopMatrix(); 

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

    // background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // whether shading is smooth or flat
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_DEPTH_TEST);
    
    sim_setup();
}

//  This function is called whenever a key event occurs.
//  The key value is in "key" and "x" and "y" hold the current mouse position
void keyboard(unsigned char key, int x, int y){
  switch( key) {
  case 'q': // quit
    building_delete( b );
    exit(0);
    break;
  case 'a':
    angle = angle-3.0;
    break;
  case 'd':
    angle = angle+3.0;
    break;
  case 'w':
    if(eyeAngle<90.0)
    eyeAngle = eyeAngle+3.0;
    break;
  case 's':
    if(eyeAngle>-90.0)
    eyeAngle = eyeAngle-3.0;
    break;
  case 'i':
    posx = posx-1;
    posz = posz-1;
    break;
  case 'k':
    posx = posx+1;
    posz = posz+1;
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
    glutCreateWindow("Testing");
    init();
    
    // set up the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // run the main loop
    glutMainLoop();
    
    return(0);
}
