/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

#define USECPP 0

/* Creates a new shape given field inputs */
Shape *shape_new( char *symbol, float *xyz, float *wdh, int *rc, int floor,
		    Attribute *a, int *dir ){
  Shape *s;
  
  s = malloc(sizeof(Shape));
  if(!s){
    printf("shape_new(): unable to allocate shape memory\n");
    return(NULL);
  }

  s->symbol = malloc(strlen(symbol) + 1);
  strcpy(s->symbol, symbol);
  
  //s->symbol = symbol;
  s->xyz[0] = xyz[0];
  s->xyz[1] = xyz[1];
  s->xyz[2] = xyz[2];
  s->wdh[0] = wdh[0];
  s->wdh[1] = wdh[1];
  s->wdh[2] = wdh[2];
  s->rc[0] = rc[0];
  s->rc[1] = rc[1];
  s->floor = floor;
  if(a){
    s->a = malloc(sizeof(Attribute));
    if(!s->a){
      printf("shape_new(): unable to allocate attribute memory\n");
      free(s);
      return(NULL);
    }
    s->a->symbol = NULL;
    attribute_copy( s->a, a );
    
    //Copy symbol over to attribute
    free(s->a->symbol);
    s->a->symbol = malloc(strlen(s->symbol)+1);
    strcpy( s->a->symbol, s->symbol );
  }
  else 
    s->a = NULL;
  s->dir[0] = dir[0];
  s->dir[1] = dir[1];
  s->dir[2] = dir[2];

  return s;
}

/* Frees memory of the fields of shape and itself */
void shape_delete( Shape *s ){
  if(s){
    if(s->symbol)
      free(s->symbol);
    if(s->a)
      attribute_delete(s->a);
    free(s);
  }
}

/* For testing purposes */
void shape_print( Shape *s ){
  printf("Symbol: %s, x: %f, y: %f, z: %f, w: %f, d: %f, h: %f, \n",
	 s->symbol, s->xyz[0], s->xyz[1], s->xyz[2], s->wdh[0], s->wdh[1],
	 s->wdh[2]);
  printf("row: %d, column: %d, floor: %d, normal: (%d, %d, %d)\n",
	 s->rc[0], s->rc[1], s->floor, s->dir[0], s->dir[1], s->dir[2]);
}
