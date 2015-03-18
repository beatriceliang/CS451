#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "graphics.h"

#define USECPP 0

Emitter *emitter_create( void ){
  Emitter *e;
  e = malloc(sizeof(Emitter));
  if(!e)
    return NULL;
  e->pSize = 0;
  e->setup = 0;
  e->pList = NULL;
  return e;
}

void emitter_init( Emitter *e ){
  e->pSize = 0;
  e->setup = 0;
  e->pList = NULL;
}


void emitter_set( Emitter *e, float *loc, int pSize){
  //printf("Entering Emitter_set");
  if(e->pList)
    free(e->pList);
  e->pList = NULL;
  e->pSize = 0;

  if(pSize > 0){
    e->pList = malloc(sizeof(Particle)*pSize);
    if(!e->pList)
      return;
    e->pSize = pSize;
  }

  e->loc[0] = loc[0];
  e->loc[1] = loc[1];
  e->loc[2] = loc[2];
  //printf("Entering Emitter_set");
}

void emitter_clear( Emitter *e ){
  if(e->pList)
    free(e->pList);
  e->pList = NULL;
  e->setup = 0;
  e->pSize = 0;
}

void emitter_free( Emitter *e ){
  if(e){
    if(e->pList)
      free(e->pList);
    free(e);
  }
}

void emitter_setup( Emitter *e ){
  //printf("Entering Emitter_setup");
  int i;
  float v[3];
  float c[3] = {0.7, 0.3, 0.3};

  for(i=0; i < e->pSize; i++){
      v[0] = ((float)rand()/(float)(RAND_MAX)-0.5)/2000.0;
      v[1] = ((float)rand()/(float)(RAND_MAX))/250;
      v[2] = ((float)rand()/(float)(RAND_MAX)-0.5)/2000.0;
      particle_set( &e->pList[i], e->loc, c, 2000, i%(e->pSize/200), v);
  }
  e->setup = 1;
  //printf("Exiting Emitter_setup");
}

/* Update the particles in the emitter */
void emitter_update( Emitter *e ){
  //printf("Entering Emitter_update");
  int i;

  if(e->setup){
    //loop through active particles
    for(i = 0; i < e->pSize; i++){
      particle_update(&e->pList[i]);
    }
  }
  else{
    emitter_setup(e);
  }
  //printf("Exiting Emitter_update");
}

void emitter_draw( Emitter *e ){
  //printf("Entering Emitter_draw");
  int i;
    glBegin(GL_BLEND);
  if(e->setup){
    //draw active particles
    for(i = 0; i < e->pSize; i++){
      if(e->pList[i].life > 0 && e->pList[i].waitTime == 0){
        glPushMatrix();
        glColor4f(e->pList[i].color[0], e->pList[i].color[1], 
        e->pList[i].color[2], e->pList[i].color[3]);
        glTranslatef(e->pList[i].loc[0], e->pList[i].loc[1], e->pList[i].loc[2]);
        glutSolidSphere(0.001, 10, 10);
        glPopMatrix();
      }
    }
  }
  else{
    emitter_setup(e);
  }
  //printf("Exiting Emitter_draw");
    glEnd();
}
