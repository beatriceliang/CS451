/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

  return b;
}

/* Divide into facades no less than 3x4x3's */
void building_init( Building *b, int w, int d, int h, int roof ){
  float wdh[3];
  float xyz[3];
  int rc[2];
  int dir[3];
  int r,c,l;
  float rwdh[3] = { (float)(w), (float)(d), 1.0 };

  b->rows = (int)(d/3.0);
  b->cols = (int)(w/3.0);
  b->floors = (int)((h-1)/4.0);

  wdh[0] = w/((float)(b->cols));
  wdh[1] = d/((float)(b->rows));
  wdh[2] = h/((float)(b->floors));

  xyz[0] = 0.0;
  xyz[1] = 0.0;
  xyz[2] = (float)(h) - 1.0;
  rc[0] = 0;
  rc[1] = 0;
  dir[0] = 0;
  dir[1] = 1;
  dir[2] = 0;
  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, NULL, dir));

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
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}

	

      }
    }
  }
}

/* Divide up building by user specification */
void building_setup( Building *b, int w, int d, int h, int roof, 
		     int width, int depth, int height, Attribute *a ){
  float wdh[3];
  float xyz[3];
  int rc[2];
  int dir[3];
  int r,c,l;
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
  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, NULL, dir));

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
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	}

      }
    }
  }
}

/* Frees memory of the fields of building and itself */
void building_delete( Building *b ){

  if(b){
    if(b->active)
      ll_delete( b->active );
    if(b->design)
      ll_delete( b->design );
    free(b);
  }
}




