#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
  int i;
  float v[3];
  float c[3] = {0.2, 0.2, 0.2};

  for(i=0; i < e->pSize; i++){
    v[0] = (float)rand()/20.0;
    v[1] = 0.05;
    v[2] = (float)rand()/20.0;
    particle_set( &e->pList[i], e->loc, c, 20, 10*(i%5), v);
  }
  e->setup = 1;
}

/* Update the particles in the emitter */
void emitter_update( Emitter *e ){
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
}

