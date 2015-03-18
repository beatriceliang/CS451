#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "graphics.h"

#define USECPP 0

/* returns an allocated Particle pointer initialized so that 
   fields are 0 or NULL */
Particle *particle_create( void ){
  Particle *p;
  p = malloc(sizeof(Particle));
  if(!p){
    return NULL;
  }
  p->life = 0;
  p->burnt = 0;
  return p;
}

/* returns an allocated Polygon pointer with the vertex list 
   initialized to a copy of the points in vlist */
Particle *particle_createp(float *location, float *c, 
			   int l, int wait, float *velocity){
  Particle *p;
  p = malloc(sizeof(Particle));
  if(!p){
    return NULL;
  }

  p->loc[0] = location[0];
  p->loc[1] = location[1];
  p->loc[2] = location[2];
  p->color[0] = c[0];
  p->color[1] = c[1];
  p->color[2] = c[2];
  p->color[3] = c[3];
  p->waitTime = wait;
  p->life = l;
  p->speed[0] = velocity[0];
  p->speed[1] = velocity[1];
  p->speed[2] = velocity[2];
  p->burnt = 0;
  return p;
}

/* frees the Particle pointer */
void particle_free(Particle *p){
  if(p){
    free(p);
  }
}

/* initializes the existing Particle to an empty Particle */
void particle_init(Particle *p){
  p->life = 0;
  p->burnt = 0;
}


/* Sets the particles to the given parameters */
void particle_set(Particle *p, float *location, float *c, 
		  int l, int wait, float *velocity){
  p->loc[0] = location[0];
  p->loc[1] = location[1];
  p->loc[2] = location[2];
  p->color[0] = c[0];
  p->color[1] = c[1];
  p->color[2] = c[2];
  p->color[3] = c[3];
  p->waitTime = wait;
  p->life = l;
  p->burnt = 0;
  p->speed[0] = velocity[0];
  p->speed[1] = velocity[1];
  p->speed[2] = velocity[2];
}

/* copies the particle data structure */
void particle_copy(Particle *to, Particle *from){
  to->loc[0] = from->loc[0];
  to->loc[1] = from->loc[1];
  to->loc[2] = from->loc[2];
  to->color[0] = from->color[0];
  to->color[1] = from->color[1];
  to->color[2] = from->color[2];
  to->color[3] = from->color[3];
  to->waitTime = from->waitTime;
  to->life = from->life;
  to->speed[0] = from->speed[0];
  to->speed[1] = from->speed[1];
  to->speed[2] = from->speed[2];
}

/* Print location of particle */
void particle_print(Particle *p, FILE*fp){
  fprintf(fp, " ( %lf, %lf, %lf ) \n", 
	  p->loc[0], p->loc[1], p->loc[2]);
}
