/* 
   Beatrice Liang and Jenny Lin 
   Spring 2015 

   Linked List data structure
   Modified from Bruce's CS351 code

*/

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

#define USECPP 0

/* Creates a new linked list and returns a pointer to it */
LinkedList *ll_new( void ) {
  LinkedList *ll;

  ll = malloc(sizeof(LinkedList));
  if( !ll ) {
    printf("ll_new(): unable to allocate list memory\n");
    return(NULL);
  }
  
  ll->head = NULL;
  ll->current = ll->head;
  ll->tail = ll->head;
  return(ll);
}

/* Adds Shape to the end of the list */
void ll_add( LinkedList *ll, Shape *item ) {
  Node *n;

  // see if the list is empty
  if( ll->head == NULL ) {
    n = malloc(sizeof(Node));
    n->next = NULL;
    n->data = item;
    ll->head = n;
    ll->tail = ll->head;
    return;
  }
  
  // goes at the end
  n = malloc(sizeof(Node));
  n->data = item;
  n->next = NULL;
  ll->tail->next = n;
  ll->tail = n;
  return;
}

/*
  Returns true if the list is empty
*/
int ll_empty( LinkedList *ll ) {
  if( ll->head == NULL )
    return(1);
  return(0);
}

/* Return a pointer to the top item in the list */
Shape *ll_peek( LinkedList *ll ) {
  if( ll->head == NULL )
    return(NULL);
  
  return(ll->head->data);
}

/* Sets the current iterator to the head of the list and 
   returns the data from the first node */
Shape *ll_head( LinkedList *ll ) {
  ll->current = ll->head;
  if( ll->current != NULL )
    return( ll->current->data );
  
  return(NULL);
}

/* Returns the data from the next element in the list as specified by
   the iterator.  Returns NULL if the end of the list has been reached */
Shape *ll_next( LinkedList *ll ) {
  if( ll->current != NULL )
    ll->current = ll->current->next;
  
  if( ll->current != NULL )
    return( ll->current->data );
  
  return(NULL);
}

/* Removes the top element from the list and returns it */
Shape *ll_pop( LinkedList *ll ) {
  Node *n;
  Shape *node_data;
  
  if( ll->head == NULL )
    return(NULL);
  
  n = ll->head;
  ll->head = ll->head->next;
  
  node_data = n->data;
  free(n);
  
  return( node_data );
}

/* Deletes all elements of the list and the list itself, 
   freeing each node's content */
void ll_delete( LinkedList *ll ) { 
  Node *p, *q;
  
  p = ll->head;
  while( p != NULL ) {
    q = p->next;
    if( p->data != NULL )
      shape_delete( p->data );
    free(p);
    p = q;
  }
  free( ll );	
  return;
}

/* Print out list for testing purposes */
void ll_print( LinkedList *ll ) {
  Shape *s;

  s = ll_head( ll );

  while( s ){
    shape_print(s);
    s = ll_next( ll );
  }

}
