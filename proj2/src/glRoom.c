#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tiffio.h>
#include <math.h>
#include "tiff-util.h"

#define TextureWidth 512
#define TextureHeight 512
#define TextureNumber 5

GLubyte texData[TextureNumber][TextureHeight][TextureWidth][4];
GLuint texName[TextureNumber];
double angle = 0.0;
double posx = 15.0;
double posz = -15.0;
double eyeAngle = 0.0;

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

/* Version of glutSolidCube that handles texture */
void mySolidCube(int texNum){
    glBindTexture(GL_TEXTURE_2D, texName[texNum]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[texNum]);
    
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    // Back Face
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    // Bottom Face
    glNormal3f( 0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    // Left Face
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();
}

/* Create the base for table and chairs */
void createBase(float height, float length, float width, int tc){
    glPushMatrix();
    glScalef(0.5, height, 0.5);
    glTranslatef( length-0.5, 0.5, width-0.5);
    mySolidCube(tc);
    glTranslatef( (-2*length)+1.0, 0, 0);
    mySolidCube(tc);
    glTranslatef(0, 0, (-2*width)+1.0);
    mySolidCube(tc);
    glTranslatef( (2*length)-1.0, 0, 0);
    mySolidCube(tc);
    glPopMatrix();
    glPushMatrix();
    glScalef(length, 0.5, width);
    glTranslatef( 0, (height+0.25)*2, 0);
    mySolidCube(tc);
    glPopMatrix();
}

/* creates the back of the chair */
void createChair( float length ){
    glColor3f(1.0, 1.0, 0.0);
    createBase( 2.5, length, 4, 4);
    glPushMatrix();
    glScalef(length, 4, 0.5);
    glTranslatef( 0, 1.25, 3.5);
    mySolidCube(4);
    glPopMatrix();
}

/* create a table with 4 chairs, making a set */
void createSet(float tHeight, float tLength, float tWidth, float cLength){
    //makes the table
    createBase(tHeight, tLength, tWidth, 1);
    glPushMatrix();
    //makes the chair
    glTranslatef( 0.0, 0.0, 4.0 );
    createChair(cLength);
    glPopMatrix();
    glPushMatrix();
    glRotatef( 90, 0.0, 1.0, 0.0 );
    glTranslatef( 0.0, 0.0, 4.0 );
    createChair(cLength);
    glPopMatrix();
    glPushMatrix();
    glRotatef( 180, 0.0, 1.0, 0.0 );
    glTranslatef( 0.0, 0.0, 4.0 );
    createChair(cLength);
    glPopMatrix();
    glPushMatrix();
    glRotatef( 270, 0.0, 1.0, 0.0 );
    glTranslatef( 0.0, 0.0, 4.0 );
    createChair(cLength);
    glPopMatrix();
}

/* draw glut primitives into scene */
void drawPrimitives( void ){

  glBindTexture(GL_TEXTURE_2D, 0);
  //sphere
  glPushMatrix();
  glColor3f(0.6, 0.6, 0.3);  
  glTranslatef( 0.0, 0.5, 0.0 );
  glutSolidSphere(1.0, 30, 30);
  glPopMatrix();
  //cone
  glPushMatrix();
  glColor3f(0.3, 0.9, 0.9);
  glTranslatef( 16.5, 1.0, 0.0 );
  glRotatef( -90.0, 1.0, 0.0, 0.0);
  glutSolidCone( 1.0, 2.0, 20, 20 );
  glPopMatrix();
  //torus
  glPushMatrix();
  glColor3f(0.9, 0.3, 0.6);
  glTranslatef( -16.5, 1.0, 0.0 );
  glRotatef( 90.0, 1.0, 0.0, 0.0);
  glutSolidTorus(0.3, 1.0, 20, 20);
  glPopMatrix();
  //cube
  glPushMatrix();
  glColor3f( 0.3, 0.3, 0.9);
  glTranslatef( 0.0, 0.5, 16.5 );
  glutSolidCube( 1.0 );
  //dodecahedron
  glColor3f( 0.6, 0.9, 0.3);
  glTranslatef( 16.5, 0.8, 0.0 );
  glutSolidOctahedron();
  //octahedron
  glColor3f( 0.9, 0.6,0.6);
  glTranslatef( -33.0, 1.0, 0.0 );
  glutSolidDodecahedron();
  //tetrahedron
  glColor3f(0.3, 0.6, 0.9);
  glTranslatef( 0.0, -1.0, -33.0 );
  glutSolidTetrahedron();
  //Icosahedron
  glColor3f(0.9, 0.9, 0.6);
  glTranslatef( 16.5, 0.0, 0.0 );
  glutSolidIcosahedron();
  //teapot
  glColor3f(0.6, 0.3, 0.3);
  glTranslatef( 16.5, 0.0, 0.0 );
  glutSolidTeapot( 1.0 );
  glPopMatrix();
}

// main display functions
void display(void) {

  GLfloat position0[] = {-19.5, 19.5, -19.5, 1.0};
  GLfloat position1[] = {-19.5, 19.5, 19.5, 1.0};
  GLfloat position2[] = { 19.5, 19.5, 19.5, 1.0};
  GLfloat position3[] = { 19.0, 19.5, -19.0, 1.0};
  int i;

  // clear the image
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  glLoadIdentity();
  
  // set up the light
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glLightfv(GL_LIGHT2, GL_POSITION, position2);
  glLightfv(GL_LIGHT3, GL_POSITION, position3);
 
  gluLookAt(posx, 10.0, posz, 
	    posx+8.0*sin(angle*M_PI/180.0), 
	    5.0+(4*sin(eyeAngle*M_PI/180.0)), 
	    posz+8.0*cos(angle*M_PI/180.0), 
	    0.0, 1.0, 0.0);   
  /* set the texturing function */
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  
  /* set the correct texture to the active texture */
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[0]);
  

  //Draw the wall, floor and ceiling
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, -20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(20.0, 0.0, -20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(20.0, 0.0, 20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(-20.0, 0.0, 20.0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, texName[2]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureHeight, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, 20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(-20.0, 20.0, 20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 20.0, -20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(-20.0, 0.0, -20.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, -20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(-20.0, 20.0, -20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(20.0, 20.0, -20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(20.0, 0.0, -20.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 0.0, -20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(20.0, 20.0, -20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(20.0, 20.0, 20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(20.0, 0.0, 20.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 0.0, 20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(20.0, 20.0, 20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 20.0, 20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(-20.0, 0.0, 20.0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, texName[3]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureHeight, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 20.0, 20.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(-20.0, 20.0, 20.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 20.0, -20.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(20.0, 20.0, -20.0);
  glEnd();

  glPushMatrix();
  glTranslatef( 8.0, 0.0, 8.0 );
  createSet(4, 8, 8, 4);
  glTranslatef( -16.0, 0.0, 0.0 );
  createSet(4, 8, 8, 4);
  glTranslatef( 0.0, 0.0, -16.0 );
  createSet(4, 8, 8, 4);
  glTranslatef( 16.0, 0.0, 0.0 );
  createSet(4, 8, 8, 4);
  glPopMatrix();
  
  drawPrimitives();
    
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureHeight, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData[3]);

    
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 3, 3, 5, 50, 13);

  // flush the drawing commands
  glFlush();

  usleep(10000);
  glutPostRedisplay();

  
}

// resize window function
void reshape(int w, int h) {
  // set the drawing viewport to the new window size
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
  // update the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective((GLdouble)75, (GLdouble)w / (GLdouble)h, (GLdouble)2, (GLdouble)50);
  
  // go back to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
}

/* keyboard listener with camera control */
void keyboard(unsigned char key, int x, int y) {
  //right is positive
  switch(key){
  case 'q':
    exit(0);
    break;
  case 'w':
    posx = posx+(sin(angle*3.14159/180.0)*0.5); 
    posz = posz+(cos(angle*3.14159/180.0)*0.5); 
    break;
  case 's':
    posx = posx-(sin(angle*3.14159/180.0)*0.5); 
    posz = posz-(cos(angle*3.14159/180.0)*0.5); 
    break;
  case 'a':
    posz = posz-(sin(angle*3.14159/180.0)*0.5);
    posx = posx+(cos(angle*3.14159/180.0)*0.5); 
    break;
  case 'd':
    posz = posz+(sin(angle*3.14159/180.0)*0.5); 
    posx = posx-(cos(angle*3.14159/180.0)*0.5); 
    break;
  case 'j':
    angle = angle+3.0;
  break;
  case 'l':
    angle = angle-3.0;
    break;
  case 'k':
    if(eyeAngle>-90.0)
      eyeAngle = eyeAngle-3.0;
    break;
  case 'i':
    if(eyeAngle<90.0)
    eyeAngle = eyeAngle+3.0;
    break;
  default:
    break;
  }
}

// initialize the lighting and material color values
void initlights(void) {
  GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
  GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat mat_diffuse[] = {0.3, 0.9, 0.5, 1.0};
  GLfloat mat_specular[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_shininess[] = {50.0};
  
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
  glEnable(GL_DEPTH_TEST); // important, or you can see through the sphere
	
}


void init(void) {
  // set the clear color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  // set the shade model to smooth
  glShadeModel(GL_SMOOTH);

  initlights();

  /* enable texturing */
  glEnable(GL_TEXTURE_2D);
  
  /* call this because we haven't packed things */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // read in the texture data
  createTextureImage("floor.tif", 512, 512, 0);
  glGenTextures(1, &texName[0]);
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  /* set the texture so it clamps at the edge */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  createTextureImage("walnut.tif", 512, 512, 1);
  glGenTextures(1, &texName[1]);
  glBindTexture(GL_TEXTURE_2D, texName[1]);
  /* set the texture so it clamps at the edge */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  createTextureImage("wall.tif", 512, 512, 2);
  glGenTextures(1, &texName[2]);
  glBindTexture(GL_TEXTURE_2D, texName[2]);
  /* set the texture so it clamps at the edge */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  createTextureImage("ceiling.tif", 512, 512, 3);
  glGenTextures(1, &texName[3]);
  glBindTexture(GL_TEXTURE_2D, texName[3]);
  /* set the texture so it clamps at the edge */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  createTextureImage("chair.tif", 512, 512, 4);
  glGenTextures(1, &texName[4]);
  glBindTexture(GL_TEXTURE_2D, texName[4]);
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

}


// main function
int main(int argc, char **argv) {
  
  // initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Room Scene");
  init();
  
  // callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  
  // main loop
  glutMainLoop();

  return(0);
}
