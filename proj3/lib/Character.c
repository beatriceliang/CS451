#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

/* create a character */
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

/* free character set */
void set_free( CharSet *c ){
  int i;
  if(c->type == 0){
    for( i=0; i < 10; i++)
      free(&c->chars[i]);
  }
  else{
    for(i=0; i <96; i++)
      free(&c->chars[i]);
  }
  free(&c->chars);
  free(c);
}

/* read characters into character sets */
void char_read(CharSet *c){
  int i;
  char filename[8];
  //10 char set
  if(c->type == 0){
    c->chars[0] = *create_char("32.ppm");
    c->chars[1] = *create_char("46.ppm");
    c->chars[2] = *create_char("58.ppm");
    c->chars[3] = *create_char("45.ppm");
    c->chars[4] = *create_char("61.ppm");
    c->chars[5] = *create_char("43.ppm");
    c->chars[6] = *create_char("42.ppm");
    c->chars[7] = *create_char("35.ppm");
    c->chars[8] = *create_char("37.ppm");
    c->chars[9] = *create_char("64.ppm");
  }
  else{
    for( i = 32; i < 127; i++ ){
      sprintf(filename, "%d.ppm", i);
      c->chars[i-32] = *create_char(filename);
    }
  }
}

/* calculate intensity of each character*/
void set_intensity(CharSet *c){
  int i,j,k;
  float rgb;

  if(c->type == 0){
    for( i=0; i<10; i++){
      rgb = 0; 
      for(j=0; j<c->chars[0].image->rows; j++){
	for(k=0; k<c->chars[0].image->cols; k++){
	  rgb = rgb + 
	    c->chars[i].image->data[j][k].rgb[0] +
	    c->chars[i].image->data[j][k].rgb[1] +
	    c->chars[i].image->data[j][k].rgb[2];
	}
      }
      c->chars[i].intensity = rgb/
	(c->chars[0].image->rows * c->chars[0].image->cols);
    }
  }
  else{
    for( i=0; i<96; i++){
      rgb = 0; 
      for(j=0; j<c->chars[0].image->rows; j++){
	for(k=0; k<c->chars[0].image->cols; k++){
	  rgb = rgb + 
	    c->chars[i].image->data[j][k].rgb[0] +
	    c->chars[i].image->data[j][k].rgb[1] +
	    c->chars[i].image->data[j][k].rgb[2];
	}
      }
      c->chars[i].intensity = rgb/
	(c->chars[0].image->rows * c->chars[0].image->cols);
    }
  }
}
