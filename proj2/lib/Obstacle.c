#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "graphics.h"

Obstacle *obstacle_create(void){
  Obstacle *o;
  int i;
  o = malloc(sizeof(Obstacle));
  if(!o)
    return NULL;
  for(i=0; i < 6; i++){
    o->coords[i] = 0.0;
  }
  for(i=0; i<3; i++){
    o->force[i] = 0.0;
  }
  o->type = 0;
  return o;
}

void obstacle_init( Obstacle *o ){
  int i;
  for(i=0; i < 6; i++){
    o->coords[i] = 0.0;
  }
  for(i=0; i<3; i++){
    o->force[i] = 0.0;
  }
  o->type = 0;
}

void obstacle_set( Obstacle *o, float *xyz, float speed, int type){
  int i;
  for(i=0; i < 6; i++){
    o->coords[i] = xyz[i];
  }
  o->force[type] = speed;
  o->type = type;
}

