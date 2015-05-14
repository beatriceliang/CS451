/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

//Color data structure
typedef struct{
  float c[3];
} Color;

//Attribute data structure
typedef struct{
  char *symbol; //indicates what type of shape attribute is for
  int step; // 0 if no step
  int ks; //0 if no keystone
  int corniceNum; //number of layers (prisms)
  int bWindow; // 0 if no band window
  int balc; // 0 if no balcony
  int winDiv[2]; //horizontal and vertical divider
  float ratio[2]; //range of acceptable window length to height ratio
  Color primary;
  Color secondary;
  Color wood;
} Attribute;


//Shape data structure
typedef struct{
  char *symbol; //shape label
  float xyz[3]; //coord of its lower left corner
  float wdh[3]; // width, depth, height of block
  int rc[2]; //block the shape belongs to
  int floor; // floor the shape belongs to
  Attribute *a; //Attritubes associated with shape
  int dir[3]; //front facing direction of shape (for 3D drawings), normal
} Shape;

// Node data structure
typedef struct{
  Shape *data;
  void *next;
} Node;

// List data structure
typedef struct{
  Node *head;
  Node *current; //used for iterator
  Node *tail;
} LinkedList;

typedef struct{
  int door; //whether or not door location has been set
  LinkedList *active; //active shapes to be partitioned
  LinkedList *design; //terminal building design
  Attribute **lib;
  Attribute **window;
  int rows;
  int cols;
  int floors;
  int numFacade; //number of facade on first floor (used for random door)
} Building;


Attribute *attribute_new( void );
Attribute **attribute_lib( void );
Attribute *attribute_match( Attribute **lib, Attribute *a );
void attribute_copy( Attribute *to, Attribute *from );
void attribute_delete( Attribute *a );

Shape *shape_new( char *symbol, float *xyz, float *wdh, int *rc, int floor,
		  Attribute *a, int *dir );
void shape_delete( Shape *s );
void shape_print ( Shape *s ); 

LinkedList *ll_new( void ); 
void ll_delete( LinkedList *ll ); 
void ll_add( LinkedList *ll, Shape *item );
Shape *ll_peek( LinkedList *ll );
Shape *ll_head( LinkedList *ll );
Shape *ll_next( LinkedList *ll );
Shape *ll_pop( LinkedList *ll );
int ll_empty( LinkedList *ll );
void ll_print( LinkedList *ll );

Building *building_new( void );
void building_init( Building *b, int w, int d, int h, int roof ); 
void building_setup( Building *b, int w, int d, int h, int roof, 
		     int width, int depth, int height, Attribute *a ); 
void building_partition( Building *b );
void building_delete( Building *b );
#endif
