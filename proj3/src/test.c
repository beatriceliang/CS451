#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

int main(int argc, char *argv[]){

  int i;
  CharSet *c;
  
  c = set_create(0);
  char_read(c);
  set_intensity(c);

  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f\n", i, c->chars[i]->intensity);
  }

  set_free(c);
}
    
