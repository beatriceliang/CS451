/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

#define USECPP 0

/* Set all fields to null if possible */
void attribute_init( Attribute *a ){
  a->symbol = NULL;
}

/* Copies attribute from from to to */
void attribute_copy( Attribute *to, Attribute *from ){
  if(to->symbol)
    free(to->symbol);

  to->symbol = malloc(strlen(from->symbol) + 1);
  strcpy(to->symbol, from->symbol);
}

/* Frees memory of the fields of attribute and itself */
void attribute_delete( Attribute *a ){
  if(a){
    if(a->symbol)
      free(a->symbol);
    free(a);
  }
}
