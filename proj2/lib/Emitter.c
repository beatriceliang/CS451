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
      particle_set( &e->pList[i], e->loc, c, 1000, i%(e->pSize/200), v);
  }
  e->setup = 1;
  //printf("Exiting Emitter_setup");
}

/* Update the particles in the emitter */
void emitter_update( Emitter *e, Obstacle *o, Wind *w){
  //printf("Entering Emitter_update");
  int i, j, k;
  float dist;
  float wdist;
  float dSpeed[3];
  Particle *p;
  int x,y,z; //0 if no collision in specified direction
    
   
    
  x = 0; y = 0; z = 0;
  if(e->setup){
    //loop through active particles
    for(j = 0; j < e->pSize; j++){
      p = &e->pList[j];
      // dead particle
      if( p->life != 0 ){
	// waiting particle
	if( p->waitTime > 0 )
	  p->waitTime--;
	else{
	  //active particle w/ life
	  p->life--;
        wdist = (w->coords[0]- p->loc[0])*(w->coords[0]- p->loc[0])+(w->coords[1]- p->loc[1])*(w->coords[1]- p->loc[1])+(w->coords[2]- p->loc[2])*(w->coords[2]- p->loc[2]);
        dist = (e->loc[0]-p->loc[0])*(e->loc[0]-p->loc[0])+(e->loc[1]-p->loc[1])*(e->loc[1]-p->loc[1])+(e->loc[2]-p->loc[2])*(e->loc[2]-p->loc[2]);

	  for (i = 0; i < 3; i++){
	    p->speed[i] = p->speed[i]+((float)rand()/(float)(RAND_MAX)-0.5)/7000.0;
          dSpeed[i] = p->speed[i] + w->speed[i]/wdist;
	  }
      	  //changes colors of particles so they get redder as they get further from the emitter
	  for(i= 0; i <3; i++){
	    p->color[i] = 1.0/ ((dist*(float)(i+0.1)+1)*(dist*(float)(i+0.1)+1)*(dist*(float)(i+0.1)+1)*(dist*(float)(i+0.1)+1));
	  }
	  //looping through obstacles
	  for(k=0; k <1; k++){
	    // printf("Entering \n");
	    //collides from the left
        if(p->loc[0] <= o[k].coords[0] &&
	       (p->loc[0] + p->speed[0]) >= o[k].coords[0]&& 
	       (p->loc[1] >= o[k].coords[2] && p->loc[1] <= o[k].coords[3]) &&
	       (p->loc[2] >= o[k].coords[4] && p->loc[2] <= o[k].coords[5])){
	      p->loc[0] = p->loc[0] -  dSpeed[0];
	      printf("left collision \n");
	    }
	    //collides from the right
	    else {
	      if(p->loc[0] >= o[k].coords[1] && 
		 (p->loc[0] + p->speed[0]) <= o[k].coords[1]&& 
		 (p->loc[1] >= o[k].coords[2] && p->loc[1] <= o[k].coords[3]) &&
		 (p->loc[2] >= o[k].coords[4] && p->loc[2] <= o[k].coords[5])){
		p->loc[0] = p->loc[0] -  dSpeed[0];
		printf("right collision \n");
	      }
	    }
	    //collides from the bottom and in the region of plane
	    if(p->loc[1] <= o[k].coords[2] &&
	       (p->loc[1] + p->speed[1]) >= o[k].coords[2] && 
	       (p->loc[0] >= o[k].coords[0] && p->loc[0] <= o[k].coords[1]) &&
	       (p->loc[2] >= o[k].coords[4] && p->loc[2] <= o[k].coords[5])){
            //printf("collide %.6f, %.6f\n",p->loc[1],p->speed[0]);
	      p->loc[1] = p->loc[1] -  dSpeed[1];
	      //printf("colliding from bottom \n");
	    }
	    //collides from the top
	    else{ 
	      if(p->loc[1] >= o[k].coords[3] && 
		 (p->loc[1] + p->speed[1]) <= o[k].coords[3]&& 
		 (p->loc[0] >= o[k].coords[0] && p->loc[0] <= o[k].coords[1]) &&
		 (p->loc[2] >= o[k].coords[4] && p->loc[2] <= o[k].coords[5])){
		p->loc[1] = p->loc[1] - dSpeed[1];
		printf("top collision \n");
	      }
	    }
	    //collides from the back
	    if(p->loc[2] <= o[k].coords[4] && 
	       (p->loc[2] + p->speed[2]) >= o[k].coords[4]&& 
	       (p->loc[0] >= o[k].coords[0] && p->loc[0] <= o[k].coords[1]) &&
	       (p->loc[1] >= o[k].coords[2] && p->loc[1] <= o[k].coords[3])){
	      p->loc[2] = p->loc[2] -  dSpeed[2];
	      printf("back collision \n");
	    }
	    //collides from the front
	    else{ 
	      if(p->loc[2] >= o[k].coords[5] && 
		 (p->loc[2] + p->speed[2]) <= o[k].coords[5]&& 
		 (p->loc[0] >= o[k].coords[0] && p->loc[0] <= o[k].coords[1]) &&
		 (p->loc[1] >= o[k].coords[2] && p->loc[1] <= o[k].coords[3])){
		p->loc[2] = p->loc[2] -  dSpeed[2];
		printf("front collision \n");
	      }
	    }
	  }
        //particle_print(p,stdout);
        for (i = 0; i < 3; i++)
            p->loc[i] = p->loc[i] +dSpeed[i];
        
	}
      }
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
  glEnd();
}
