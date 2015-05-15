/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
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
  b->door = 0;
  return b;
}

/* Divide into facades no less than 3x4x3's */
void building_init( Building *b, int w, int d, int h, int roof ){
  float wdh[3];
  float xyz[3];
  int rc[2];
  int dir[3];
  int r,c,l;
  int counter = 0;
  float rwdh[3] = { (float)(w), (float)(d), 1.0 };

  b->height = h-1;

  b->rows = (int)(d/3.0);
  b->cols = (int)(w/3.0);
  b->floors = (int)((h-1)/4.0);

  wdh[0] = w/((float)(b->cols));
  wdh[1] = d/((float)(b->rows));
  wdh[2] = (h-1)/((float)(b->floors));

  xyz[0] = 0.0;
  xyz[1] = 0.0;
  xyz[2] = (float)(h) - 1.0;
  rc[0] = 0;
  rc[1] = 0;
  dir[0] = 0;
  dir[1] = 1;
  dir[2] = 0;
  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, attribute_new(), dir));

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
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, 
					attribute_new(), dir));
	  counter++;
	}	
      }
    }
    if(l == 0)
      b->numFacade = counter;
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
  int counter = 0;
  float rwdh[3] = { (float)(w), (float)(d), 1.0 };

  b->height = h-1;

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
  if(a->winDiv[0] == 0 && a->winDiv[1] == 0)
    a->ks = 1;

  ll_add( b->design, shape_new( "R", xyz, rwdh, rc, 0, a, dir));

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
	  counter++;
	}
	if(r == b->rows-1){
	  dir[0] = 0;
	  dir[1] = 0;
	  dir[2] = -1;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
	if(c == 0){
	  dir[0] = -1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
	if(c == b->cols-1){
	  dir[0] = 1;
	  dir[1] = 0;
	  dir[2] = 0;
	  ll_add( b->active, shape_new( "F", xyz, wdh, rc, l, NULL, dir));
	  counter++;
	}
      }
    }
    if( l == 0 )
      b->numFacade = counter;
  }
}

void building_partition( Building *b ){
  Shape *s;
  int i, doorNum;
  float xyz[3];
  float wdh[3];
  int dir[3];

  s = ll_pop( b->active );
  i = 0;
  srand(time(NULL));
  rand();
  doorNum = rand() % b->numFacade;

  while(s){
    
    //set door at this shape
    if( b->door == 0  && i == doorNum){
      b->door = 1;
      xyz[0] = s->xyz[0];
      xyz[1] = s->xyz[1] + (s->wdh[2]*0.2);
      xyz[2] = s->xyz[2];
      //add wall around door
      if(s->dir[2] == 0){
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1]/8;
      }
      else{
	wdh[0] = s->wdh[0]/8;
	wdh[1] = s->wdh[1];
      }
      wdh[2] = s->wdh[2]*0.8;
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
      				    s->a, s->dir ) );
      xyz[0] = s->xyz[0] + ((wdh[0]*7)*s->dir[2]*s->dir[2]);
      xyz[2] = s->xyz[2] - ((wdh[1]*7)*s->dir[0]*s->dir[0]);
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
      				    s->a, s->dir ) );
      xyz[0] = s->xyz[0] + (wdh[0]*s->dir[2]*s->dir[2]);
      xyz[1] = s->xyz[1] + (s->wdh[2]*0.8);
      xyz[2] = s->xyz[2] - (wdh[1]*s->dir[0]*s->dir[0]);
      if(s->dir[2] == 0){
	wdh[0] = wdh[0];
	wdh[1] = wdh[1]*6;
      }
      else{
	wdh[0] = wdh[0]*6;
	wdh[1] = wdh[1];
      }
      wdh[2] = s->wdh[2]/5;
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
      				    s->a, s->dir ) );
      

      Color_copy(&s->a->primary, &s->a->secondary);     
      //band component of door
      wdh[2] = s->wdh[2]*0.2;
      if(s->dir[2] == 0){
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1]/8;
      }
      else{
	wdh[0] = s->wdh[0]/8;
	wdh[1] = s->wdh[1];
      }
      ll_add( b->design, shape_new( "WALL", s->xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );

      xyz[0] = s->xyz[0] + ((wdh[0]*7)*s->dir[2]*s->dir[2]);
      xyz[1] = s->xyz[1];
      xyz[2] = s->xyz[2] - ((wdh[1]*7)*s->dir[0]*s->dir[0]);
      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );

      xyz[0] = s->xyz[0] + ((s->wdh[0]/8)*s->dir[2]*s->dir[2]);
      xyz[1] = s->xyz[1];
      xyz[2] = s->xyz[2] - ((s->wdh[1]/8)*s->dir[0]*s->dir[0]);
      wdh[2] = s->wdh[2]*0.8;
      if(s->dir[2] == 0){
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1]*0.75;
      }
      else{
	wdh[0] = s->wdh[0]*0.75;
	wdh[1] = s->wdh[1];
      }
     ll_add( b->active, shape_new( "DOOR", xyz, wdh, s->rc, s->floor, 
				    s->a, s->dir ) );
      shape_delete(s);
      s = ll_pop(b->active);
    }
    else{
      //First floor non-doors; partition into band and F1
      if( s->floor == 0 && strcmp(s->symbol, "F") == 0 ){
	i++;

	xyz[0] = s->xyz[0];
	xyz[1] = s->xyz[1] + (s->wdh[2]/5);	
	xyz[2] = s->xyz[2];
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1];
	wdh[2] = s->wdh[2]*0.8;
	ll_add( b->active, shape_new( "F1", xyz, wdh, s->rc, s->floor,
				      s->a, s->dir ) );

	Color_copy(&s->a->primary, &s->a->secondary);
	
  	xyz[0] = s->xyz[0];
	xyz[1] = s->xyz[1];
	xyz[2] = s->xyz[2];
	wdh[0] = s->wdh[0];
	wdh[1] = s->wdh[1];
	wdh[2] = s->wdh[2]/5;
	ll_add( b->active, shape_new( "BAND", xyz, wdh, s->rc, s->floor,
				      s->a, s->dir ) );


	shape_delete(s);
	s = ll_pop(b->active);
      }
      //Don't need else if b/c diff floor conditions, aka doesnt affect door
      //Second floor facade w/ no cornice
      else {
	if( s->floor == 1 && strcmp(s->symbol, "F") == 0 ){
	  wdh[0] = s->wdh[0];
	  wdh[1] = s->wdh[1];
	  wdh[2] = s->wdh[2]/7;
	  ll_add( b->active, shape_new( "CORNICE", s->xyz, wdh, s->rc, s->floor,
					s->a, s->dir ) );
	  xyz[0] = s->xyz[0];
	  xyz[1] = s->xyz[1]+wdh[2];
	  xyz[2] = s->xyz[2];
	  wdh[2] = wdh[2]*6;
	  ll_add( b->active, shape_new( "F1", xyz, wdh, s->rc, s->floor, 
	  				s->a, s->dir ) );
	  shape_delete(s);
	  s = ll_pop(b->active);
	}
	//Divides facades into wall and window and maybe keystone
	else{
	  if( (s->floor > 1 && strcmp( s->symbol, "F") == 0) || 
	      (strcmp( s->symbol, "F1" ) == 0) ){
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = 2.0*s->wdh[1]/7.0;
	    }
	    else{
	      wdh[0] = 2.0*s->wdh[0]/7.0;
	      wdh[1] = s->wdh[1];
	    }
	    wdh[2] = s->wdh[2];
	    ll_add( b->design, shape_new( "WALL", s->xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	    xyz[0] = s->xyz[0] + ((wdh[0]*2.5)*s->dir[2]*s->dir[2]);
	    xyz[1] = s->xyz[1];
	    xyz[2] = s->xyz[2] - ((wdh[1]*2.5)*s->dir[0]*s->dir[0]);
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = 3.0*s->wdh[1]/7.0;
	    }
	    else{
	      wdh[0] = 3.0*s->wdh[0]/7.0;
	      wdh[1] = s->wdh[1];
	    }

	    wdh[2] = wdh[2]/4.0;
	    xyz[0] = s->xyz[0] + ((2.0*s->wdh[0]/7.0)*s->dir[2]*s->dir[2]);
	    xyz[2] = s->xyz[2] - ((2.0*s->wdh[1]/7.0)*s->dir[0]*s->dir[0]);
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );
	   
	    /******************************************/
	    /*******DOESN'T ACTUALLY BELONG HERE*******/
	    /*********WITH ACTUAL WINDOW PLACEMENT*****/
	    /******************************************/
	    if(s->dir[0] == 0){
	      //top frame
	      xyz[0] = s->xyz[0] + s->wdh[0]*2.0/7.0;
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.75;
	      wdh[0] = s->wdh[0]*3.0/7.0;
	      wdh[1] = 0.25;
	      wdh[2] = 0.0;
	      dir[0] = 0;
	      dir[1] = -1;
	      dir[2] = 0;
	      if(s->dir[2] == 1)
		xyz[2] = s->xyz[2];
	      else
		xyz[2] = s->xyz[2] - s->wdh[1] + 0.25;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	      //bottom frame 
	      xyz[1] = s->xyz[1];
	      wdh[2] = s->wdh[2]/4.0;
	      dir[1] = 1;
	      if(s->dir[2] == 1)
		xyz[2] = s->xyz[2];
	      else
		xyz[2] = s->xyz[2] - s->wdh[1] + 0.25;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	      //left frame
	      xyz[0] = s->xyz[0];
	      xyz[1] = s->xyz[1] + wdh[2];
	      wdh[0] = s->wdh[0]*2.0/7.0;
	      wdh[1] = 0.25;
	      wdh[2] = wdh[2]*2;
	      dir[1] = 0;
	      dir[0] = 1;
	      if(s->dir[2] == 1)
		xyz[2] = s->xyz[2];
	      else
		xyz[2] = s->xyz[2] - s->wdh[1] + 0.25;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );

	      //right frame
	      xyz[0] = xyz[0] + s->wdh[0]*5.0/7.0;
	      dir[0] = -1;
	      if(s->dir[2] == 1)
		xyz[2] = s->xyz[2];
	      else
		xyz[2] = s->xyz[2] - s->wdh[1] + 0.25;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	    }
	    else{
	      //top frame  
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.75;
	      xyz[2] = s->xyz[2] - (s->wdh[1]*2.0/7.0);
	      wdh[0] = 0.25;
	      wdh[1] = s->wdh[1]*3.0/7.0;
	      wdh[2] = 0.0;
	      dir[0] = 0;
	      dir[1] = -1;
	      dir[2] = 0;
	      if(s->dir[0] == 1)
		xyz[0] = s->xyz[0] + s->wdh[0] - 0.25;
	      else
		xyz[0] = s->xyz[0];
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	      
	      //bottom frame 
	      xyz[1] = s->xyz[1];
	      wdh[2] = s->wdh[2]/4.0;
	      dir[1] = 1;
	      if(s->dir[0] == 1)
		xyz[0] = s->xyz[0] + s->wdh[0] - 0.25;
	      else
		xyz[0] = s->xyz[0] ;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	      //left frame
	      xyz[2] = s->xyz[2];
	      xyz[1] = s->xyz[1] + (s->wdh[2]*0.25);
	      wdh[0] = 0.25;
	      wdh[1] = s->wdh[1]*2.0/7.0;
	      wdh[2] = s->wdh[2]*0.5;
	      dir[1] = 0;
	      dir[2] = -1;
	      if(s->dir[0] == 1)
		xyz[0] = s->xyz[0] + s->wdh[0] - 0.25;
	      else
		xyz[0] = s->xyz[0];
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					    s->a, dir ) );
	      
	      //right frame
	      xyz[2] = xyz[2] - s->wdh[1]*5.0/7.0;
	      dir[2] = 1;
	      if(s->dir[0] == 1)
		xyz[0] = s->xyz[0] + s->wdh[0] - 0.25;
	      else
		xyz[0] = s->xyz[0];
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
	      s->a, dir ) );
	    }	      
	   
	    /******************************************/
	    /*******DOESN'T ACTUALLY BELONG HERE*******/
	    /*********WITH ACTUAL WINDOW PLACEMENT*****/
	    /*****************ENDS HERE****************/
	    /******************************************/
	    /*
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = 3.0*s->wdh[1]/7.0;
	    }
	    else{
	      wdh[0] = 3.0*s->wdh[0]/7.0;
	      wdh[1] = s->wdh[1];
	    }

	    wdh[2] = wdh[2]/4.0;
	    xyz[0] = s->xyz[0] + ((2.0*s->wdh[0]/7.0)*s->dir[2]*s->dir[2]);
	    xyz[2] = s->xyz[2] - ((2.0*s->wdh[1]/7.0)*s->dir[0]*s->dir[0]);
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );

	    */
	    xyz[0] = s->xyz[0] + ((2.0*s->wdh[0]/7.0)*s->dir[2]*s->dir[2]);
	    xyz[1] = s->xyz[1] + s->wdh[2]*0.75;
	    xyz[2] = s->xyz[2] - ((2.0*s->wdh[1]/7.0)*s->dir[0]*s->dir[0]);
	    wdh[2] = s->wdh[2]/4;
	    if(s->dir[2] == 0){
	      wdh[0] = s->wdh[0];
	      wdh[1] = s->wdh[1]*3.0/7.0;
	    }
	    else{
	      wdh[0] = s->wdh[0]*3.0/7.0;
	      wdh[1] = s->wdh[1];
	    }  
	    ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					  s->a, s->dir ) );

	    wdh[2] = wdh[2]*2;
	    //bind window to top and bottom
	    if((s->dir[2] == 0 && wdh[1]/wdh[2] > s->a->ratio) || 
	       (s->dir[0] == 0 && wdh[0]/wdh[2] > s->a->ratio) ){
	      if(s->dir[2] == 0){
		wdh[0] = s->wdh[0]; 
		wdh[1] = ((s->wdh[1]*3.0/7.0) - (s->a->ratio*s->wdh[2]*0.5))*0.5;
	      }
	      else{
		wdh[0] = ((s->wdh[0]*3.0/7.0) - (s->a->ratio*s->wdh[2]*0.5))*0.5;
		wdh[1] = s->wdh[1];
	      }
	      xyz[0] = s->xyz[0] + ((s->wdh[0]*2.0/7.0)*s->dir[2]*s->dir[2]);
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.25;
	      xyz[2] = s->xyz[2] - ((s->wdh[1]*2.0/7.0)*s->dir[0]*s->dir[0]);
	      wdh[2] = s->wdh[2]*0.5;
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
	      				    s->a, s->dir ) );
	      xyz[0] = s->xyz[0] + (((5.0*s->wdh[0]/7.0) - wdh[0])*s->dir[2]*s->dir[2]);
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.25;
	      xyz[2] = s->xyz[2] - (((5.0*s->wdh[1]/7.0) - wdh[1])*s->dir[0]*s->dir[0]);
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
	      				    s->a, s->dir ) );
	      //add the window
	      xyz[0] = s->xyz[0] + (((s->wdh[0]*2.0/7.0)+wdh[0])*s->dir[2]*s->dir[2]) - (0.2*s->dir[0]);
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.25;
	      xyz[2] = s->xyz[2] - (((s->wdh[1]*2.0/7.0)+wdh[1])*s->dir[0]*s->dir[0]) - (0.2*s->dir[2]);
	      wdh[2] = s->wdh[2]*0.5;
	      if(s->dir[0] == 0){
		wdh[0] = s->a->ratio*s->wdh[2]*0.5;
		wdh[1] = s->wdh[1];
		ll_add( b->active, shape_new( "WIN", xyz, wdh, s->rc, s->floor, 
					      s->a, s->dir ) );
	      }
	      else{
		wdh[0] = s->wdh[0];
		wdh[1] = s->a->ratio*s->wdh[2]*0.5;
		ll_add( b->active, shape_new( "WIN", xyz, wdh, s->rc, s->floor, 
					      s->a, s->dir ) );
	      }
	    }
	    
	    //bind window to left and right
	    if((s->dir[2] == 0 && wdh[1]/wdh[2] < s->a->ratio) || 
	       (s->dir[0] == 0 && wdh[0]/wdh[2] < s->a->ratio) ){
	      if(s->dir[2] == 0){
		wdh[0] = s->wdh[0]; 
		wdh[1] = s->wdh[1]*3.0/7.0;
		wdh[2] = ((s->wdh[2]*0.5) - ((1.0/s->a->ratio)*s->wdh[1]*0.5))*0.5;
	      }
	      else{
		wdh[0] = s->wdh[0]*3.0/7.0;
		wdh[1] = s->wdh[1];
		wdh[2] = ((s->wdh[2]*0.5) - ((1.0/s->a->ratio)*s->wdh[1]*0.5))*0.5;
	      }
	      xyz[0] = s->xyz[0] + ((s->wdh[0]*2.0/7.0)*s->dir[2]*s->dir[2]);
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.25;
	      xyz[2] = s->xyz[2] - ((s->wdh[1]*2.0/7.0)*s->dir[0]*s->dir[0]);
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
	      				    s->a, s->dir ) );
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.75-wdh[2];
	      ll_add( b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
	      				    s->a, s->dir ) );
	      
	      //add the window
	      xyz[0] = s->xyz[0] + ((s->wdh[0]*2.0/7.0)*s->dir[2]*s->dir[2]) - (0.2*s->dir[0]);
	      xyz[1] = s->xyz[1] + s->wdh[2]*0.25 + wdh[2];
	      xyz[2] = s->xyz[2] - ((s->wdh[1]*2.0/7.0)*s->dir[0]*s->dir[0]) - (0.2*s->dir[2]);
	      wdh[2] = (1.0/s->a->ratio)*s->wdh[1]*0.5;
	      if(s->dir[0] == 0){
		wdh[0] = s->wdh[0]*3.0/7.0;
		wdh[1] = s->wdh[1];
		ll_add( b->active, shape_new( "WIN", xyz, wdh, s->rc, s->floor, 
					      s->a, s->dir ) );
	      }
	      else{
		wdh[0] = s->wdh[0];
		wdh[1] = s->wdh[1]*3.0/7.0;
		ll_add( b->active, shape_new( "WIN", xyz, wdh, s->rc, s->floor, 
					      s->a, s->dir ) );
	      }
	    }
	    

	    //has keystone
	    if( s->a->ks == 1 && s->floor < 2){
	      Color_copy( &s->a->primary, &s->a->secondary );
	      xyz[1] = s->xyz[1] + s->wdh[2]*3.5/4.0;
	      if(s->dir[2] == 1){
		xyz[0] = s->xyz[0] + (s->wdh[0]/2);
		xyz[2] = s->xyz[2];
	      }
	      if(s->dir[2] == -1){	       
		xyz[0] = s->xyz[0] + (s->wdh[0]/2);
		xyz[2] = s->xyz[2] - s->wdh[1];
	      }
	      if(s->dir[0] == 1){
		xyz[0] = s->xyz[0] + s->wdh[0];
		xyz[2] = s->xyz[2] - (s->wdh[1]/2);
	      }
	      if(s->dir[0] == -1){
		xyz[0] = s->xyz[0];
		xyz[2] = s->xyz[2] - (s->wdh[1]/2);
	      }
	      wdh[0] = s->wdh[0];
	      wdh[1] = s->wdh[1];
	      //height of keystone
	      wdh[2] = s->wdh[2]/6;
	      ll_add( b->design, shape_new( "KS", xyz, wdh, s->rc, s->floor, 
					    s->a, s->dir ) );
	    }
	    shape_delete(s);
	    s = ll_pop(b->active);
	
	  }
	  else{
	    //divide balcony into tiny windows if true
	    if( strcmp( s->symbol, "BAND" ) == 0 && s->a->bWindow == 0 ){
	      ll_add( b->design, shape_new( "WALL", s->xyz, s->wdh, s->rc, s->floor, 
					    s->a, s->dir ) );
	      shape_delete(s);
	      s = ll_pop(b->active);
	    }
	    else{
	      //divide cornice into sublayers
	      if( strcmp( s->symbol, "CORNICE") == 0 ){
		Color_copy( &s->a->primary, &s->a->secondary );
		for( i = 0; i < s->a->corniceNum; i++){
		  if(s->dir[0] == 0){
		    xyz[0] = s->xyz[0] - ((i+1)*0.15);
		    xyz[1] = s->xyz[1] + s->wdh[2]*(i)/s->a->corniceNum;
		    if(s->dir[2] == -1)
		      xyz[2] = s->xyz[2] - s->wdh[1];
		    else
		      xyz[2] = s->xyz[2];
		    wdh[0] = s->wdh[0] + ((i+1)*0.30);
		    wdh[1] = 0.15*(i+1);
		    wdh[2] = s->wdh[2] - s->wdh[2]*(i)/s->a->corniceNum;
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		  }
		  else{ 
		    if(s->dir[0] == 1)
		      xyz[0] = s->xyz[0]+s->wdh[0];
		    else
		      xyz[0] = s->xyz[0];
		    xyz[1] = s->xyz[1] + s->wdh[2]*(i)/s->a->corniceNum;
		    xyz[2] = s->xyz[2] + ((i+1)*0.15);
		    wdh[0] = 0.15*(i+1);
		    wdh[1] = s->wdh[1] + ((i+1)*0.30);
		    wdh[2] = s->wdh[2] - s->wdh[2]*(i)/s->a->corniceNum;
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		  }
		}
		shape_delete(s);
		s = ll_pop(b->active);

	      }

	      else{
		if( strcmp( s->symbol, "DOOR") == 0 ){
		  //frame of door
		  Color_copy( &s->a->primary, &s->a->secondary );
		  if(s->dir[0] == 0){
		    xyz[0] = s->xyz[0];
		    xyz[1] = s->xyz[1];
		    if(s->dir[2] == -1)
		      xyz[2] = s->xyz[2] - s->wdh[1] + 0.1;
		    else
		      xyz[2] = s->xyz[2]-0.1;
		    wdh[0] = s->wdh[0]/10;
		    wdh[1] = 0.2;
		    wdh[2] = s->wdh[2];
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		    xyz[0] = s->xyz[0] + 9*wdh[0];
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		    xyz[0] = s->xyz[0];
		    xyz[1] = s->xyz[1] + s->wdh[2] - (s->wdh[0]/10);
		    wdh[0] = s->wdh[0];
		    wdh[2] = s->wdh[0]/10;
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		  }
		  else{
		    xyz[1] = s->xyz[1];
		    xyz[2] = s->xyz[2];
		    if(s->dir[0] == 1)
		      xyz[0] = s->xyz[0]+s->wdh[0] - 0.1;
		    else
		      xyz[0] = s->xyz[0] + 0.1;
		    wdh[0] = 0.2;
		    wdh[1] = s->wdh[1]/10;
		    wdh[2] = s->wdh[2];
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						 s->a, s->dir ) );
		    xyz[2] = s->xyz[2] - 9*wdh[1];
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
					       s->a, s->dir ) );
		    xyz[2] = s->xyz[2];
		    xyz[1] = s->xyz[1] + s->wdh[2] - (s->wdh[1]/10);
		    wdh[2] = s->wdh[1]/10;
		    wdh[1] = s->wdh[1];
		    ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
					       s->a, s->dir ) );
		  }
		  
		  //see if the door has steps
		  if(s->a->step == 1){
		    if(s->dir[0] == 0){
		      xyz[0] = s->xyz[0] + (s->wdh[0]/10);
		      xyz[1] = s->xyz[1];
		      if(s->dir[2] == -1)
			xyz[2] = s->xyz[2] - s->wdh[1];
		      else
			xyz[2] = s->xyz[2];
		      wdh[0] = s->wdh[0]*0.8;
		      wdh[1] = 0.20;
		      wdh[2] = 0.60;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		      if(s->dir[2] == -1)
		      xyz[2] = xyz[2] - 0.20;
		      else
			xyz[2] = s->xyz[2] + 0.20;
		      wdh[2] = 0.40;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		      if(s->dir[2] == -1)
			xyz[2] = xyz[2] - 0.20;
		      else
			xyz[2] = s->xyz[2] + 0.20;
		      wdh[2] = 0.20;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		    }
		    else{
		      xyz[1] = s->xyz[1];
		      xyz[2] = s->xyz[2] - (s->wdh[1]/10);
		      if(s->dir[0] == 1)
			xyz[0] = s->xyz[0]+s->wdh[0];
		      else
		      xyz[0] = s->xyz[0];
		      wdh[0] = 0.20;
		      wdh[1] = s->wdh[1]*0.8;
		      wdh[2] = 0.60;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		      if(s->dir[0] == 1)
		      xyz[0] = xyz[0] + 0.20;
		      else
			xyz[0] = xyz[0] - 0.20;
		      wdh[2] = 0.40;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		      if(s->dir[0] == 1)
			xyz[0] = xyz[0] + 0.20;
		      else
			xyz[0] = xyz[0] - 0.20;
		      wdh[2] = 0.20;
		      ll_add(b->design, shape_new( "PRISM", xyz, wdh, s->rc, s->floor, 
						   s->a, s->dir ) );
		 
		    }
		}
		  
		  //physical door
		  Color_copy( &s->a->primary, &s->a->wood );
		  xyz[0] = s->xyz[0] + ((s->wdh[0]/10)*s->dir[2]*s->dir[2]);
		  xyz[1] = s->xyz[1];
		  xyz[2] = s->xyz[2] - ((s->wdh[1]/10)*s->dir[0]*s->dir[0]);
		  if(s->dir[0] == 0){
		    wdh[0] = s->wdh[0]*0.8;
		    wdh[1] = s->wdh[1];
		  wdh[2] = s->wdh[2] - (s->wdh[0]/10);
		  }
		  else{
		    wdh[0] = s->wdh[0];
		    wdh[1] = s->wdh[1]*0.8;
		    wdh[2] = s->wdh[2] - (s->wdh[1]/10);
		  }
		  ll_add(b->design, shape_new( "WALL", xyz, wdh, s->rc, s->floor, 
					       s->a, s->dir ) );
		  
		  
		  shape_delete(s);
		  s = ll_pop(b->active);
		}
		else{
		  shape_delete(s);
		  s = ll_pop(b->active);
		}
	      }
	    }
	  }
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




