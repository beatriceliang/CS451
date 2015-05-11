/* 
   Beatrice Liang and Jenny Lin 
   Spring 2015 

   Unit Testing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

#define USECPP 0

int main(int argc, char *argv[]) {

  LinkedList *ll;
  Shape *s1;
  Shape *s2;
  Shape *s3;
  Shape *s4;
  Shape *s5;
  Attribute *a;

  int xyz1[3] = {1,2,3};
  float fxyz1[3] = {1,2,3};
  int rc1[2] = {1,2};
  int xyz2[3] = {2,3,4};
  float fxyz2[3] = {2,3,4};
  int rc2[2] = {2,3};
  int xyz3[3] = {3,4,5};
  float fxyz3[3] = {3,4,5};
  int rc3[2] = {3,4};
  int xyz4[3] = {4,5,6};
  float fxyz4[3] = {4,5,6};
  int rc4[2] = {4,5};
  int xyz5[3] = {5,6,7};
  float fxyz5[3] = {5,6,7};
  int rc5[2] = {5,6};
 
  a = malloc(sizeof(Attribute));
  a->symbol = malloc(4);
  strcpy( a->symbol, "WIN" );
  
  /* Memory Leak Testing */
  /* Solid 840K Memory Usage */
  /*
  while(1){

    s1 = shape_new( "s1", fxyz1, fxyz1, rc1, 1, a, xyz1 );
    s2 = shape_new( "s2", fxyz2, fxyz2, rc2, 2, a, xyz2 );
    s3 = shape_new( "s3", fxyz3, fxyz3, rc3, 3, a, xyz3 );
    s4 = shape_new( "s4", fxyz4, fxyz4, rc4, 4, a, xyz4 );
    s5 = shape_new( "s5", fxyz5, fxyz5, rc5, 5, a, xyz5 );

    ll = ll_new();
    ll_add( ll, s1 );
    ll_add( ll, s2 );
    ll_add( ll, s3 );
    ll_add( ll, s4 );
    ll_add( ll, s5 );
    
    ll_delete( ll );
  }
  */

  /* Functional testing */
  s1 = shape_new( "s1", fxyz1, fxyz1, rc1, 1, a, xyz1 );
  s2 = shape_new( "s2", fxyz2, fxyz2, rc2, 2, a, xyz2 );
  s3 = shape_new( "s3", fxyz3, fxyz3, rc3, 3, a, xyz3 );
  s4 = shape_new( "s4", fxyz4, fxyz4, rc4, 4, a, xyz4 );
  s5 = shape_new( "s5", fxyz5, fxyz5, rc5, 5, a, xyz5 );

  ll = ll_new();
  ll_add( ll, s1 );
  ll_add( ll, s2 );
  ll_add( ll, s3 );
  ll_add( ll, s4 );
  ll_add( ll, s5 );

  ll_print( ll );
  ll_delete( ll );

  free(a->symbol);
  free(a);
}


