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
  
  char_swap(c->chars[1],c->chars[2]);
  char_swap(c->chars[7],c->chars[6]);
  char_swap(c->chars[4],c->chars[9]);
  printf("*********Before Sorting********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii);
  }
  quickSort( c, 0, c->size-1 );
  printf("*********After Sorting********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii);
  }
  //image_write(c->chars[1]->image, "1.ppm");
  //image_write(c->chars[2]->image, "2.ppm");
  set_free(c);
}
    
