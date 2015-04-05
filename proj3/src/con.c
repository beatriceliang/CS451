#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i;
  char *s = malloc(strlen("convert 111.png 111.ppm "));
  
  for(i = 32; i < 127; i++){
    sprintf(s, "convert %d.png %d.ppm", i, i);
    system(s);
  }
  free(s);
}
