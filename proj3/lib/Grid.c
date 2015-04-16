#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

/* create a grid */
Grid *create_grid( char *filename ){
  int i, r, c;

  Grid *g = malloc(sizeof(Grid));
  if(!g)
    return NULL;
  //reads the image into the grid
  g->original = image_read(filename);

  r = g->original->rows/14;
  c = g->original->cols/12;

  //create the grid so that it's divided into 14x12 rectangles
  g->grid = malloc(sizeof(Image)*r);
  if(!g->grid){
    image_dealloc(g->original);
    free(g);
    return NULL;
  }

  //allocate memory for rgb and intensity
  g->intensity = malloc(sizeof(float)*r);
  if(!g->intensity){
    image_dealloc(g->original);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->r = malloc(sizeof(float)*r);
  if(!g->r){
    image_dealloc(g->original);
    free(g->intensity);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->g = malloc(sizeof(float)*r);
  if(!g->g){
    image_dealloc(g->original);
    free(g->intensity);
    free(g->r);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->b = malloc(sizeof(float)*r);
  if(!g->g){
    image_dealloc(g->original);
    free(g->intensity);
    free(g->r);
    free(g->g);
    free(g->grid);
    free(g);
    return NULL;
  }

  g->grid[0] = malloc(sizeof(Image)*r*c);
  if(!g->grid[0]){
    image_dealloc(g->original);
    free(g->intensity);
    free(g->r);
    free(g->g);
    free(g->b);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->intensity[0] = malloc(sizeof(float)*r*c);
  if(!g->intensity[0]){
    image_dealloc(g->original);
    free(g->intensity);
    free(g->r);
    free(g->g);
    free(g->b);
    free(g->grid[0]);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->r[0] = malloc(sizeof(float)*r*c);
  if(!g->r[0]){
    image_dealloc(g->original);
    free(g->intensity[0]);
    free(g->intensity);
    free(g->r);
    free(g->g);
    free(g->b);
    free(g->grid[0]);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->g[0] = malloc(sizeof(float)*r*c);
  if(!g->g[0]){
    image_dealloc(g->original);
    free(g->intensity[0]);
    free(g->intensity);
    free(g->r[0]);
    free(g->r);
    free(g->g);
    free(g->b);
    free(g->grid[0]);
    free(g->grid);
    free(g);
    return NULL;
  }
  g->b[0] = malloc(sizeof(float)*r*c);
  if(!g->b[0]){
    image_dealloc(g->original);
    free(g->intensity[0]);
    free(g->intensity);
    free(g->r[0]);
    free(g->r);
    free(g->g[0]);
    free(g->g);
    free(g->b);
    free(g->grid[0]);
    free(g->grid);
    free(g);
    return NULL;
  }

  for(i = 1; i < r; i++){
    g->grid[i] = &(g->grid[0][i*c]);
    g->intensity[i] = &(g->intensity[0][i*c]);
    g->r[i] = &(g->r[0][i*c]);
    g->g[i] = &(g->g[0][i*c]);
    g->b[i] = &(g->b[0][i*c]);
  }

  g->rows = r;
  g->cols = c;
  return g;
}

/* frees everything in the grid, including itself */
void grid_free(Grid *g){
  if(g){
    if(g->grid){
      if(g->grid[0]){
	free(g->grid[0]);
      }
      free(g->grid);
    }
    if(g->intensity){
      if(g->intensity[0]){
	free(g->intensity[0]);
      }
      free(g->intensity);
    }
    if(g->r){
      if(g->r[0]){
	free(g->r[0]);
      }
      free(g->r);
    }
    if(g->g){
      if(g->g[0]){
	free(g->g[0]);
      }
      free(g->g);
    }
    if(g->b){
      if(g->b[0]){
	free(g->b[0]);
      }
      free(g->b);
    }
    image_dealloc(g->original);
    free(g);
  }
}

/* reads and calculate values (intensity & rgb) and store into grid */
void read_to_grid( Grid *g ){
  int r, c;
  
  for(r = 0; r < (g->rows * 14); r++){
    for(c = 0; c < (g->cols * 12); c++){
      g->r[r/14][c/12] = g->r[r/14][c/12] + g->original->data[r][c].rgb[0];
      g->g[r/14][c/12] = g->g[r/14][c/12] + g->original->data[r][c].rgb[1];
      g->b[r/14][c/12] = g->b[r/14][c/12] + g->original->data[r][c].rgb[2];
    }
  }

  for(r = 0; r < g->rows; r++){
    for(c = 0; c < g->cols; c++){
      //12 * 14 = 168
      g->r[r][c] = g->r[r][c]/168.0;
      g->g[r][c] = g->g[r][c]/168.0;
      g->b[r][c] = g->b[r][c]/168.0;
      g->intensity[r][c] = (g->r[r][c] + g->g[r][c] + g->b[r][c])/3.0;
      //printf("%d ,", (int)(g->intensity[r][c]));
    }
    //printf("\n");
  }
}

/* write appropriate character into grid based on intensity */
void char_to_grid( Grid *g, CharSet *c ){

  Image *temp;
  int row, col, size;


  //size of character list
  size = c->size;

  for(row = 0; row < g->rows; row++){
    for(col = 0; col < g->cols; col++){
      temp = binary_search(c, 0, size, g->intensity[row][col]);
      g->grid[row][col] = *temp;
    }
  }    

}
