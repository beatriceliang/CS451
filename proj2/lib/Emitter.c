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
  e->maxSize = 0;
  e->pList = NULL;
  return e;
}

void emitter_init( Emitter *e ){
  e->pSize = 0;
  e->maxSize = 0;
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
    e->maxSize = pSize;
  }

  e->loc[0] = loc[0];
  e->loc[1] = loc[1];
  e->loc[2] = loc[2];
}

void emitter_clear( Emitter *e ){
  if(e->pList)
    free(e->pList);
  e->maxSize = 0;
  e->pSize = 0;
}

void emitter_free( Emitter *e ){
  if(e){
    if(e->pList)
      free(e->pList);
    free(e);
  }
}
