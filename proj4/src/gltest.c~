#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "graphics.h"


Emitter *e;
Obstacle * oList[2];
Obstacle *o1, *o2;
Wind *w;

// Function for drawing the contents of the screen
void display(void) {
    
    GLfloat position[] = {10.0, 5.0, 20.0, 1.0};
    
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 0.5);
    
    // reset the modelview matrix
    glLoadIdentity();
    
    // set up the viewing transformation
    gluLookAt(0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set up the light
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    emitter_update(e, oList, w, 2);
    emitter_draw(e);
    obstacle_draw(oList, 2);
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
    float coord1[6] = { -0.37, 0.0, 0.3, 0.3, -0.2, 0.2 };
    float coord2[6] = { 0.0, 0.37, 0.15, 0.15, -0.2, 0.2 };
    float speed[3] = {0.0000, 0, 0.0};//{0.2,0.0,0.3};
    float wloc[3] = {0.06, 0.5, 0.0};//{0.05,0.2,0};
    // background color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    // whether shading is smooth or flat
    glShadeModel(GL_SMOOTH);
    
    //initlights();
    e = emitter_create();
    o1 = obstacle_create();
    o2 = obstacle_create();
    
    
    emitter_set(e, loc, 500000);
    emitter_setup( e, 500 );
    obstacle_set(o1, coord1, 0 );
    obstacle_set(o2, coord2, 0 );
    oList[0] = o1;
    oList[1] = o2;
    
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
            obstacle_free(o1);
            obstacle_free(o2);
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
    glutCreateWindow("Collision Checking");
    init();
    
    // set up the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // run the main loop
    glutMainLoop();
    
    return(0);
}
