#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tiffio.h>
#include <math.h>
#include "tiff-util.h"
#include "graphics.h"

#define TextureWidth 512
#define TextureHeight 512
#define TextureNumber 5

GLubyte texData[TextureNumber][TextureHeight][TextureWidth][4];
GLuint texName[TextureNumber];

Emitter * eList[4];
Wind *w;

// read the image file texture.tif
void createTextureImage(char *filename, int width, int height, int index) {
    uint32 row, col;
    uint32 *rawImage;
    long i, j;
    
    rawImage = tiff_read(filename, &row, &col);
    
    for(i=0;i<width;i++) {
        for(j=0;j<height;j++) {
            texData[index][i][j][0] = rawImage[i*col + j] & 0x000000FF;
            texData[index][i][j][1] = (rawImage[i*col + j] & 0x0000FF00) >> 8;
            texData[index][i][j][2] = (rawImage[i*col + j] & 0x00FF0000) >> 16;
            texData[index][i][j][3] = 255;
        }
    }
    free(rawImage);
}

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

void drawCake( void ){
    
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[0]);
    drawCylinder( 1.5f, 1.0f, 37 );
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[1]);
    glPushMatrix();
    //Candles
    glTranslatef( 0.0f, 1.0f, -1.3f );
    drawCylinder( 0.075f, 0.9f, 10);
    glTranslatef( 0.0f, 0.0f, 2.6f );
    drawCylinder( 0.075f, 0.9f, 10);
    glTranslatef( 1.3f, 0.0f, -1.3f );
    drawCylinder( 0.075f, 0.9f, 10);
    glTranslatef( -2.6f, 0.0f, 0.0f );
    drawCylinder( 0.075f, 0.9f, 10);/*
    glTranslatef( 1.95f, 0.0f, 1.125f );//0.65 & 1.125
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( -1.3f, 0.0f, -2.25f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( 1.775f, 0.0f, 1.775f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( -2.25f, 0.0f, -1.3f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( 2.25f, 0.0f, 0.0f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( -2.25f, 0.0f, 1.3f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( 1.775f, 0.0f, -1.775f );
    drawCylinder( 0.075f, 1.5f, 10);
    glTranslatef( -1.3f, 0.0f, 2.25f );
    drawCylinder( 0.075f, 1.5f, 10);*/
    glPopMatrix();
}


// Function for drawing the contents of the screen
void display(void) {
    /*
    static starttime = 0.0;
    struct timeval tp;
    struct timezone tz;
    double curtime, delta;
    
    // move emitter down every 5s
    gettimeofday( &tp, &tz );
    curtime = tp.tv_sec + tp.tv_usec/1000000.0;
    if(starttime == 0.0) {
        starttime = curtime;
    }
    delta = curtime - starttime;
    //printf("moving down %f\n", ((int)(delta * 1000) % 5000)*360.0 / 5000.0);
    if( ((int)(delta * 1000) % 5000)*360.0 / 5000.0 < 10 ){
        //emitter_move(e, 0.0, -0.5, 0.0);
        e->loc[1] = e->loc[1]-0.05;
        //printf("moving down\n");
    }
    */
    
    GLfloat position[] = {10.0, 5.0, 20.0, 1.0};
    int i;
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 0.5);
    
    // reset the modelview matrix
    glLoadIdentity();
    
    // set up the viewing transformation
    gluLookAt(0.0, 7.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set up the light
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    /* set the texturing function */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    /* set the correct texture to the active texture */
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[0]);
    
    //GLUquadricObj *quadObj = gluNewQuadric();
    //gluCylinder(quadObj, 1, 1, 1, 20, 13);
    //drawCircle( 0, 0, 0, 1, 20 );
    drawCake();
    //printf("Before emit stuff\n");
    glBindTexture(GL_TEXTURE_2D, 0);
    for(i = 0; i < 4; i++){
        emitter_update(eList[i], NULL, w, 0);
        emitter_draw(eList[i]);
    }
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
    int i;
    float loc[3] = {1.3, 1.0, 0.0};
    float speed[3] = {0.0, 0, 0.0};//{0.2,0.0,0.3};
    float wloc[3] = {0.0, 0.0, 0.0};//{0.05,0.2,0};
    // background color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    // whether shading is smooth or flat
    glShadeModel(GL_SMOOTH);
    
    //initlights();
    w = wind_create();
    wind_set(w, wloc,speed);
    
    for(i = 0; i < 4; i++) {
        eList[i] = emitter_create();
    }
    emitter_set(eList[0], loc, 70000);
    loc[0] = -1.3;
    emitter_set(eList[1], loc, 70000);
    loc[0] = 0.0;
    loc[2] = 1.3;
    emitter_set(eList[2], loc, 70000);
    loc[2] = -1.3;
    emitter_set(eList[3], loc, 70000);
    /* enable texturing */
    glEnable(GL_TEXTURE_2D);
    
    /* call this because we haven't packed things */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    
    createTextureImage("cake.tif", 512, 512, 0);
    glGenTextures(1, &texName[0]);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    /* set the texture so it clamps at the edge */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    createTextureImage("candle.tif", 512, 512, 1);
    glGenTextures(1, &texName[1]);
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    /* set the texture so it clamps at the edge */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glEnable(GL_DEPTH_TEST);

}

//  This function is called whenever a key event occurs.
//  The key value is in "key" and "x" and "y" hold the current mouse position
void keyboard(unsigned char key, int x, int y){
    int i;
    
    switch( key) {
        case 'q': // quit
            for(i = 0; i < 4; i++){
                emitter_free(eList[i]);
            }
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
    glutCreateWindow("CAKE!");
    init();
    
    // set up the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // run the main loop
    glutMainLoop();
    
    return(0);
}
