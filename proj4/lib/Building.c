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
