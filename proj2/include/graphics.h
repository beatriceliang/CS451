#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct{
  float loc[3]; //x,y,z coordinates
  float color[4]; //r,g,b,alpha
  //vec3 dir; //direction of movement     
  int life; //lifetime left
  float speed[3]; //velocity
} Particle;

typedef struct{
  float loc[3]; //x,y,z coordinates
  int pSize; //number of active particles
  Particle *pList; //list of particles emitted
  int maxSize; //maximum capacity of particles
} Emitter;

/* Particle */
Particle *particle_create( void );
Particle *particle_createp(float *location, float *c, 
			   /*vec3 direction,*/ int l, float *velocity);
void particle_free(Particle *p);

void particle_init(Particle *p);
void particle_set(Particle *p, float *location, float *c, 
		  /*vec3 direction,*/ int l, float *velocity);
void particle_copy(Particle *to, Particle *from);
void particle_print(Particle *p, FILE*fp);

/* Emitter */
Emitter *emitter_create( void );
void emitter_init( Emitter *e );
void emitter_set( Emitter *e, float *loc, int pSize);
void emitter_clear( Emitter *e );
void emitter_free( Emitter *e );

#endif
