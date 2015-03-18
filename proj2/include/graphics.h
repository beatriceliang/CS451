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
  int waitTime;//rounds until active
  float speed[3]; //velocity
  int burnt; //0 if not, 1 if yes
} Particle;

typedef struct{
  float loc[3]; //x,y,z coordinates
  int pSize; //number of active particles
  Particle *pList; //list of particles emitted
  int setup; //0 if false and 1 if true
} Emitter;

typedef struct{
  float coords[6];
  int type; // 0: horizontal, 1: Vertical in z , 2: Vertical in x
} Obstacle;

typedef struct{
    float coords[3];
    float speed[3];
} Wind;

/* Particle */
Particle *particle_create( void );
Particle *particle_createp(float *location, float *c, 
			   int l, int wait, float *velocity);
void particle_free(Particle *p);

void particle_init(Particle *p);
void particle_set(Particle *p, float *location, float *c, 
		  int l, int wait, float *velocity);
void particle_copy(Particle *to, Particle *from);
void particle_print(Particle *p, FILE*fp);
void particle_update( Particle *p );

/* Emitter */
Emitter *emitter_create( void );
void emitter_init( Emitter *e );
void emitter_set( Emitter *e, float *loc, int pSize);
void emitter_move( Emitter *e, float dx, float dy, float dz );
void emitter_clear( Emitter *e );
void emitter_free( Emitter *e );
void emitter_update( Emitter *e, Obstacle **o, Wind *w, int size );
void emitter_setup( Emitter *e, int life );
void emitter_draw( Emitter *e );

/* Obstacle */
Obstacle *obstacle_create(void);
void obstacle_free( Obstacle *o );
void obstacle_init( Obstacle *o );
void obstacle_set( Obstacle *o, float *xyz, int type );
void obstacle_draw( Obstacle **o, int size );

/* Wind */
Wind *wind_create(void);
void wind_free( Wind *o );
void wind_init( Wind *o );
void wind_set( Wind *o, float *xyz, float *speed);

#endif
