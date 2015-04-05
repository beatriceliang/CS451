#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

Character *create_char( char *filename ){
  Character *c = malloc(sizeof(Character));
  if(!c) 
    return NULL;
  c->image = image_read(filename);
  return c;
}

/* create empty character set */
CharSet *create_set(int type){

  CharSet *c = malloc(sizeof(CharSet));
  if(!c)
    return NULL;

  if(type == 0){
    c->chars = malloc(sizeof(Character)*10);
    if(!c->chars){
      free(c);
      return NULL;
    }
    c->type = 0;
    return c;
  }
  c->chars = malloc(sizeof(Character)*95);
    if(!c->chars){
      free(c);
      return NULL;
    }
    c->type = 0;
    return c;
}

/* read characters into character sets */
void char_read(CharSet *c){
}
