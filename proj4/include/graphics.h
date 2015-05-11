/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

// Node data structure
typedef struct {
  Shape *data;
  Shape *next;
} Node;

// List data structure
typedef struct {
  Node *head;
  Node *current; //used for iterator
  Node *tail;
} LinkedList;



LinkedList *ll_new( void ); 
void ll_delete( LinkedList *ll ); 
void ll_add( LinkedList *ll, Shape *item );
Shape *ll_peek( LinkedList *ll );
Shape *ll_head( LinkedList *ll );
Shape *ll_next( LinkedList *ll );
Shape *ll_pop( LinkedList *ll );
int ll_empty( LinkedList *ll );
