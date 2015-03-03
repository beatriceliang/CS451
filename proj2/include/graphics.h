#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct {
  float loc[3]; //x,y,z coordinates
  float alpha; //alpha value
  float color[3]; //color of particle
  vec3 dir; //direction of movement     
  int life; //lifetime left
  float speed[3]; //velocity
} Particle;


Particle *particle_create( void );
Particle *particle_createp(float *location, float a, float *c, 
			 vec3 direction, int l, float *velocity);
void particle_free(Particle *p);

void particle_init(Particle *p);
void particle_set(Particle *p, float *location, float a, float *c, 
		  vec3 direction, int l, float *velocity);
void particle_copy(Particle *to, Particle *from);
void particle_print(Particle *p, FILE*fp);
  
