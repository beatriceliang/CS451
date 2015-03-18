#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "graphics.h"

Wind *wind_create(void){
    Wind *w;
    int i;
    w = malloc(sizeof(Wind));
    if(!w)
        return NULL;
    for(i=0; i < 3; i++){
        w->coords[i] = 0.0;
        w->speed[i] = 0.0;
    }
    return w;
}

void wind_free( Wind *w ){
    if(w)
        free(w);
}

void wind_init( Wind *w ){
    int i;
    for(i=0; i < 3; i++){
        w->coords[i] = 0.0;
        w->speed[i] = 0.0;
    }
    
}

void wind_set( Wind *w, float *xyz, float *speed){
    int i;
    for(i=0; i < 3; i++){
        w->coords[i] = xyz[i];
         w->speed[i] = speed[i];
    }
   
}

