#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "graphics.h"


Emitter *e;
Wind *w;

void drawCircle(float x, float y, float z, float r, int slices){
    int i;
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( x, y, z);
    for(i=0; i<=slices; i++){
        glVertex3f( x + (r * cos(i * 2.0f*M_PI / slices)),
                   y,
                   z + (r * sin(i * 2.0f*M_PI / slices)));
    }
    glEnd();
}

void drawCylinder( float r, float h, int slices){
    GLUquadricObj *quadObj = gluNewQuadric();
    glPushMatrix();
    glRotatef( 90.0, 1.0, 0.0, 0.0);
    gluCylinder(quadObj, r, r, h, slices, 1);
    glPopMatrix();
    drawCircle( 0, 0, 0, r, slices );
    drawCircle( 0, -h, 0, r, slices );
}


// Function for drawing the contents of the screen
void display(void) {
    
    GLfloat position[] = {10.0, 5.0, 20.0, 1.0};
    
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 0.5);
    
    // reset the modelview matrix
    glLoadIdentity();
    
    // set up the viewing transformation
    gluLookAt(0.0, 0.5, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set up the light
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    emitter_update(e, NULL, w, 0);
    emitter_draw(e);
    
    drawCylinder( 0.1f, 2.0f, 30 );
    //draw everything
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
    float speed[3] = {0.0003, 0, 0.0};//{0.2,0.0,0.3};
    float wloc[3] = {0.06, 0.7, 0.0};//{0.05,0.2,0};
    // background color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    // whether shading is smooth or flat
    glShadeModel(GL_SMOOTH);
    
    //initlights();
    e = emitter_create();
    emitter_set(e, loc, 500000);
    emitter_setup( e, 500 );
    
    w = wind_create();
    wind_set(w, wloc, speed);
    
    glEnable(GL_DEPTH_TEST);
    
}

//  This function is called whenever a key event occurs.
//  The key value is in "key" and "x" and "y" hold the current mouse position
void keyboard(unsigned char key, int x, int y){
    switch( key) {
        case 'q': // quit
            emitter_free(e);
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
    glutCreateWindow("Wind");
    init();
    
    // set up the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // run the main loop
    glutMainLoop();
    
    return(0);
}
