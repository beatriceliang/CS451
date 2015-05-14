/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

#define USECPP 0

/* Set all fields to default facade */
Attribute *attribute_new( void ){
  Attribute *a;
  a = malloc(sizeof(Attribute));

  if(!a){
    printf("attribute_new(): unable to allocate attribute memory\n");
    return(NULL);
  }
  a->symbol = malloc(2);
  strcpy( a->symbol, "F" );
  a->step = 1;
  a->ks = 1;
  a->corniceNum = 2;
  a->bWindow = 0;
  a->wood.c[0] = 0.395; 
  a->wood.c[1] = 0.168;
  a->wood.c[2] = 0.0;
  a->secondary.c[0] = 0.836; 
  a->secondary.c[1] = 0.715;
  a->secondary.c[2] = 0.660;
  a->primary.c[0] = 0.691; 
  a->primary.c[1] = 0.539;
  a->primary.c[2] = 0.426;
  a->winDiv[0] = 0;
  a->winDiv[1] = 0;
  a->ratio[0] = 2.0/3.0;
  a->ratio[1] = 2.0/3.0;
  a->balc = 0;
  return a;
}

/* Build an attribute library. Returns array of Attribute pointer */
Attribute **attribute_lib( void ){
  return NULL;
}

/* Returns attribute of best match */
Attribute *attribute_match( Attribute **lib, Attribute *a ){
  return NULL;
}

/* Copies attribute from from to to */
void attribute_copy( Attribute *to, Attribute *from ){
  if(to->symbol)
    free(to->symbol);
  to->symbol = malloc(strlen(from->symbol) + 1);
  strcpy(to->symbol, from->symbol);

  to->step = from->step;
  to->ks = from->ks;
  to->corniceNum = from->corniceNum;
  to->bWindow = from->bWindow;
  Color_copy( &to->wood, &from->wood );
  Color_copy( &to->secondary, &from->secondary );
  Color_copy( &to->primary, &from->primary );
  to->winDiv[0] = from->winDiv[0];
  from->winDiv[1] = from->winDiv[1];
  to->ratio[0] = from->ratio[0];
  to->balc = from->balc;
}

/* Frees memory of the fields of attribute and itself */
void attribute_delete( Attribute *a ){
  if(a){
    if(a->symbol)
      free(a->symbol);
    free(a);
  }
}

/* copies the Color data. */
void Color_copy(Color *to, Color *from){
  to->c[0] = from->c[0];
  to->c[1] = from->c[1];
  to->c[2] = from->c[2];
}
