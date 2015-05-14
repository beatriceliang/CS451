/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "graphics.h"

#define USECPP 0


/* Creates a new building with empty shape lists */
Building *building_new( void ){

  Building *b;
  b = malloc(sizeof(Building));

  if(!b){
    printf("building_new(): unable to allocate building memory\n");
    return(NULL);
  }

  b->active = ll_new();
  b->design = ll_new();
  b->door = 0;
  b->lib = attribute_lib();
  return b;
}

/* Divide into facades no less than 3x4x3's */
void building_init( Building *b, int w, int d, int h, int roof ){
  float wdh[3];
  float xyz[3];
  int rc[2];
  int dir[3];
  int r,c,l;
  int counter = 0;
  float rwdh[3] = { (float)(w), (float)(d), 1.0 };

  b->rows = (int)(d/3.0);
  b->cols = (int)(w/3.0);
  b->floors = (int)((h-1)/4.0);

  wdh[0] = w/((float)(b->cols));
  wdh[1] = d/((float)(b->rows));
  wdh[2] = (h-1)/((float)(b->floors));

  xyz[0] = 0.0;
  xyz[1] = 0.0;
  xyz[2] = (float)(h) - 1.0;
  rc[0] = 0;
  rc[1] = 0;
  dir[0] = 0;
  dir[1] = 1;
  dir[2] = 0;
  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, attribute_new(), dir));

  for(l = 0; l < b->floors; l++){
    for(c = 0; c < b->cols; c++){
      for(r = 0; r < b->rows; r++){
	xyz[0] = wdh[0]*c;
	xyz[1] = wdh[2]*l;
	xyz[2] = -wdh[1]*r;
	rc[0] = r;
	rc[1] = c;
	if(r == 0){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = 1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}	
      }
    }
    if(l == 0)
      b->numFacade = counter;
  }
  printf("exiting building_init\n");
}

/* Divide up building by user specification */
void building_setup( Building *b, int w, int d, int h, int roof, 
		     int width, int depth, int height, Attribute *a ){
  float wdh[3];
  float xyz[3];
  int rc[2];
  int dir[3];
  int r,c,l;
  int counter = 0;
  float rwdh[3] = { (float)(w), (float)(d), 1.0 };

  b->rows = (int)(d/depth);
  b->cols = (int)(w/width);
  b->floors = (int)((h-1)/height);

  wdh[0] = (float)w/((float)(b->cols));
  wdh[1] = (float)d/((float)(b->rows));
  wdh[2] = (float)h/((float)(b->floors));

  xyz[0] = 0.0;
  xyz[1] = 0.0;
  xyz[2] = (float)(h) - 1.0;
  rc[0] = 0;
  rc[1] = 0;
  dir[0] = 0;
  dir[1] = 1;
  dir[2] = 0;
  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, a, dir));

  for(l = 0; l < b->floors; l++){
    for(c = 0; c < b->cols; c++){
      for(r = 0; r < b->rows; r++){
	xyz[0] = wdh[0]*c;
	xyz[1] = wdh[2]*l;
	xyz[2] = wdh[1]*r;
	rc[0] = r;
	rc[1] = c;
	if(r == 0){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = 1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
      }
    }
    if( l == 0 )
      b->numFacade = counter;
  }
}

void building_partition( Building *b ){
  Shape *s;
  int i, doorNum;
  float xyz[3];
  float wdh[3];

  s = ll_pop( b->active );
  i = 0;
  srand(time(NULL));
  rand();
  doorNum = rand() % b->numFacade;

  while(s){
    
    //set door at this shape
    if( b->door == 0  && i == doorNum){
      b->door = 1;
      //add wall around door
      if(s->dir[2] == 0){
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1]/8;
      }
      else{
	wdh[0] = s->wdh[0]/8;
	wdh[1] = s->wdh[1];
      }
      wdh[2] = s->wdh[2];
      ll_add( b->design, shape_new( "WALL", s->xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );
      xyz[0] = s->xyz[0] + ((wdh[0]*7)*s->dir[2]*s->dir[2]);
      xyz[1] = s->xyz[1];
      xyz[2] = s->xyz[2] - ((wdh[1]*7)*s->dir[0]*s->dir[0]);
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );
      xyz[0] = s->xyz[0] + (wdh[0]*s->dir[2]*s->dir[2]);
      xyz[1] = s->xyz[1] + (s->wdh[2]*0.8);
      xyz[2] = s->xyz[2] - (wdh[1]*s->dir[0]*s->dir[0]);
      if(s->dir[2] == 0){
	wdh[0] = wdh[0];
	wdh[1] = wdh[1]*6;
      }
      else{
	wdh[0] = wdh[0]*6;
	wdh[1] = wdh[1];
      }
      wdh[2] = s->wdh[2]/5;
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );
      xyz[1] = s->xyz[1];
      wdh[2] = s->wdh[2]*0.8;
      ll_add( b->active, shape_new( "DOOR", xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );
      shape_delete(s);
      s = ll_pop(b->active);
    }
    else{
      //First floor non-doors; partition into band and F1
      if( s->floor == 0 && strcmp(s->symbol, "F") == 0 ){
	i++;
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1];
	wdh[2] = s->wdh[2]/5;
	ll_add( b->active, shape_new( "BAND", s->xyz, wdh, s->rc, s->floor,
				      s->a, s->dir ) );
	xyz[0] = s->xyz[0];
	xyz[1] = s->xyz[1] + wdh[2];	
	xyz[2] = s->xyz[2];
	wdh[2] = wdh[2]*4;
	ll_add( b->active, shape_new( "F1", xyz, wdh, s->rc, s->floor,
				      s->a, s->dir ) );
	shape_delete(s);
	s = ll_pop(b->active);
      }
      //Don't need else if b/c diff floor conditions, aka doesnt affect door
      //Second floor facade w/ no cornice
      else {
	if( s->floor == 1 && strcmp(s->symbol, "F") == 0 ){
	  wdh[0] = s->wdh[0];
	  wdh[1] = s->wdh[1];
	  wdh[2] = s->wdh[2]/7;
	  ll_add( b->active, shape_new( "CORNICE", s->xyz, wdh, s->rc, s->floor,
					s->a, s->dir ) );
	  xyz[0] = s->xyz[0];
	  xyz[1] = s->xyz[1]+wdh[2];
	  xyz[2] = s->xyz[2];
	  wdh[2] = wdh[2]*6;
	  ll_add( b->active, shape_new( "F1", xyz, wdh, s->rc, s->floor, 
					s->a, s->dir ) );
	  shape_delete(s);
	  s = ll_pop(b->active);
	}
	//Divides facades into wall and window and maybe keystone
	else{
	  if( (s->floor > 1 && strcmp( s->symbol, "F") == 0) || 
	      (strcmp( s->symbol, "F1" ) == 0) ){
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = 2.0*s->wdh[1]/7.0;
	    }
	    else{
	      wdh[0] = 2.0*s->wdh[0]/7.0;
	      wdh[1] = s->wdh[1];
	    }
	    wdh[2] = s->wdh[2];
	    ll_add( b->design, shape_new( "WALL", s->xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	    xyz[0] = s->xyz[0] + ((wdh[0]*2.5)*s->dir[2]*s->dir[2]);
	    xyz[1] = s->xyz[1];
	    xyz[2] = s->xyz[2] - ((wdh[1]*2.5)*s->dir[0]*s->dir[0]);
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = 3.0*s->wdh[1]/7.0;
	    }
	    else{
	      wdh[0] = 3.0*s->wdh[0]/7.0;
	      wdh[1] = s->wdh[1];
	    }

	    wdh[2] = wdh[2]/4.0;
	    xyz[0] = s->xyz[0] + ((2.0*s->wdh[0]/7.0)*s->dir[2]*s->dir[2]);
	    xyz[2] = s->xyz[2] - ((2.0*s->wdh[1]/7.0)*s->dir[0]*s->dir[0]);
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	    shape_delete(s);
	    s = ll_pop(b->active);
	    //has keystone
	    //if( s->a->ks == 1 ){
	  }
	  //To Be Continued
	  else{
	    shape_delete(s);
	    s = ll_pop(b->active);
	    //return;
	  }
	}
      }
    }
  }
  printf(" Existing partition\n");
}

/* Frees memory of the fields of building and itself */
void building_delete( Building *b ){
  int i;

  if(b){
    if(b->active)
      ll_delete( b->active );
    if(b->design)
      ll_delete( b->design );
    if(b->lib){
      for(i = 0; i < (sizeof(b->lib)/sizeof(Attribute)); i++)
	attribute_delete(b->lib[i]);
      free(b->lib);
    } 
    free(b);
  }
}




