#include <stdio.h>
#include <stdlib.h>
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
  o->type = 0;
  return o;
}

void obstacle_free( Obstacle *o ){
  if(o)
    free(o);
}

void obstacle_init( Obstacle *o ){
  int i;
  for(i=0; i < 6; i++){
    o->coords[i] = 0.0;
  }
  o->type = 0;
}

void obstacle_set( Obstacle *o, float *xyz, int type){
  int i;
  for(i=0; i < 6; i++){
    o->coords[i] = xyz[i];
  }
  o->type = type;
}

void obstacle_draw( Obstacle **oList, int size ){
  int i;
  Obstacle *o;
  for(i = 0; i < size; i++){
    o = oList[i];
    glBegin(GL_BLEND);
    // xz-plane
    if( o->type == 0){
      glBegin( GL_QUADS );
      glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
      glVertex3f(o->coords[0], o->coords[2], o->coords[5]);
      glVertex3f(o->coords[0], o->coords[2], o->coords[4]);
      glVertex3f(o->coords[1], o->coords[2], o->coords[4]);
      glVertex3f(o->coords[1], o->coords[2], o->coords[5]);
      glEnd();
    }
    if( o->type == 1){
      glBegin( GL_QUADS );
      glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
      glVertex3f(o->coords[0], o->coords[2], o->coords[5]);
      glVertex3f(o->coords[0], o->coords[2], o->coords[4]);
      glVertex3f(o->coords[0], o->coords[3], o->coords[4]);
      glVertex3f(o->coords[0], o->coords[3], o->coords[5]);
      glEnd();
    }
    if( o->type == 2){
      glBegin( GL_QUADS );
      glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
      glVertex3f(o->coords[0], o->coords[2], o->coords[4]);
      glVertex3f(o->coords[0], o->coords[3], o->coords[4]);
      glVertex3f(o->coords[1], o->coords[3], o->coords[4]);
      glVertex3f(o->coords[1], o->coords[2], o->coords[4]);
      glEnd();
    }
    glEnd();
  }
}
