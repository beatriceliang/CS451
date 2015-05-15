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

void my_pyramid(){
  glBegin( GL_TRIANGLES );
  glVertex3f( 0.0f, 0.5f, 0.0f );
  glVertex3f( 0.5f, -0.5f, 0.5f );
  glVertex3f( 0.5f, -0.5f, -0.5f);
  
  glVertex3f( 0.0f, 0.5f, 0.0f );
  glVertex3f( 0.5f, -0.5f, 0.5f );
  glVertex3f( -0.5f, -0.5f, 0.5f);
  
  glVertex3f( 0.0f, 0.5f, 0.0f );
  glVertex3f( -0.5f, -0.5f, -0.5f );
  glVertex3f( -0.5f, -0.5f, 0.5f);
  
  glVertex3f( 0.0f, 0.5f, 0.0f );
  glVertex3f( -0.5f, -0.5f, -0.5f );
  glVertex3f( 0.5f, -0.5f, -0.5f);
  glEnd();

  glBegin( GL_QUADS );
  glVertex3f( 0.5f, -0.5f, 0.5f );
  glVertex3f( -0.5f, -0.5f, 0.5f );
  glVertex3f( -0.5f, -0.5f, -0.5f);
  glVertex3f( 0.5f, -0.5f, -0.5f);
  glEnd();
}


void sim_setup( void ){
  b = building_new();
  building_init( b, 14, 7, 17, 1 );
  building_partition( b );
}

void shape_draw( Shape *s ){
  if( strcmp(s->symbol, "WALL") == 0 ){
    glBegin(GL_QUADS);
    glNormal3d( s->dir[0], s->dir[1], s->dir[2]);
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
    if( strcmp(s->symbol, "PRISM") == 0 ){
      glPushMatrix();
      glColor4f( s->a->primary.c[0],
		 s->a->primary.c[1],
		 s->a->primary.c[2], 1.0f );
      
      if(s->dir[0]==1){
          glTranslatef(s->xyz[0]+s->wdh[0]/2, s->xyz[1]+s->wdh[2]/2, 
		       s->xyz[2]-s->wdh[1]/2);
      }
      if(s->dir[0]==-1){
	glTranslatef(s->xyz[0]-s->wdh[0]/2, s->xyz[1]+s->wdh[2]/2,
		     s->xyz[2]-s->wdh[1]/2);
      }
      if(s->dir[2]==1){
	glTranslatef(s->xyz[0]+s->wdh[0]/2, s->xyz[1]+s->wdh[2]/2, 
		     s->xyz[2]+s->wdh[1]/2);
      }
      if(s->dir[2]==-1){
	glTranslatef(s->xyz[0]+s->wdh[0]/2, s->xyz[1]+s->wdh[2]/2, 
		     s->xyz[2]-s->wdh[1]/2);
      }
      glScalef(s->wdh[0],s->wdh[2], s->wdh[1]);
      glutSolidCube(1);
      glPopMatrix();
    }
    else if( strcmp( s->symbol, "KS" ) == 0 ){
      glPushMatrix();
      glTranslatef( s->xyz[0], s->xyz[1]-(s->wdh[2]/6), s->xyz[2] );
      //glRotated(30, 0, 1, 0);
      glRotated(180, 1, 0, 0);
      glScalef( s->wdh[2]*1.5, s->wdh[2], s->wdh[2] );
      
      //glutSolidTetrahedron();
      my_pyramid();
      glPopMatrix();
    }
    
    //Numbers are BAD!!!
    /*
    glPushMatrix();
    glTranslatef( s->wdh[0]/2.0, s->xyz[1]+(s->wdh[2]/2), -s->wdh[1]/2.0);
    glScalef(s->wdh[0], s->wdh[2], s->wdh[1]);
    glutSolidCube(1);
    glPopMatrix(); 
    */
  }
}

void draw_building( void ){
  Shape *s;
  s = ll_head( b->design );

  while( s ){
    //printf("%s \n", s->symbol);
    /*
    glColor4f( s->xyz[0]/10.0, 
	       s->xyz[1]/17.0,
	       -s->xyz[2]/10.0, 1.0f );
    */
    
    glColor4f( s->a->primary.c[0], 
	       s->a->primary.c[1],
	       s->a->primary.c[2], 1.0f );
    shape_draw( s );
    
    s = ll_next( b->design );
  }
}

// Function for drawing the contents of the screen
void display(void) {
    
  //GLfloat position[] = {20.0, 30.0, 40.0, 1.0};
  GLfloat position0[] = {-100, 70, -100, 1.0};
  GLfloat position1[] = {-100, 70, 100, 1.0};
  GLfloat position2[] = { 100, 70, 100, 1.0};
  GLfloat position3[] = { 100, 70, -100, 1.0};
  
  Shape *s;
    // clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  
  // reset the modelview matrix
  glLoadIdentity();
  
  // set up the viewing transformation
  gluLookAt((posx*sin(angle*M_PI/180.0))+5, 
	    8.0+(8*sin(eyeAngle*M_PI/180.0)), 
	    (posz*cos(angle*M_PI/180.0))-5, 
	    5.0, 8.0, -5.0, 0.0, 1.0, 0.0); 
  
  // set up the light
  
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glLightfv(GL_LIGHT2, GL_POSITION, position2);
  glLightfv(GL_LIGHT3, GL_POSITION, position3);
  
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

  GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
  GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat mat_diffuse[] = {0.3, 0.9, 0.5, 1.0};
  GLfloat mat_specular[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_shininess[] = {50.0};

  // background color
  glClearColor(1.0, 1.0, 1.0, 1.0);
  
  // whether shading is smooth or flat
  glShadeModel(GL_SMOOTH);
  
  // material values
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  
  // generic lighting values
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  
  // specific light source
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular );
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular );
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT2, GL_SPECULAR, specular );
  glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT3, GL_SPECULAR, specular );

  // enable lighting, light0 and depth testing
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  
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

// main functione
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
