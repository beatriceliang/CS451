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
  int winDiv[2]; //horizontal and vertical divider
  float ratio; //window length to height ratio
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
  int rows;
  int cols;
  int floors;
  int height; //height before roof
  int numFacade; //number of facade on first floor (used for random door)
  int doorBlock[2]; //block door belongs to
} Building;


Attribute *attribute_new( void );
void attribute_copy( Attribute *to, Attribute *from );
void attribute_delete( Attribute *a );
void Color_copy(Color *to, Color *from);

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
void building_setDoor( Building *b, int *rc );
void building_partition( Building *b );
void building_delete( Building *b );
#endif
