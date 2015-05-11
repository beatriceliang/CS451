/* 
   Beatrice Liang and Jenny Lin 
   Spring 2015 

   Linked List data structure
   Modified from Bruce's CS351 code

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
  
  ll->root = NULL;
  ll->current = ll->root;
  ll->tail = ll->root;
  return(ll);
}

/* Adds Shape to the end of the list */
void ll_add( LinkedList *ll, Shape *item ) {
  Node *n;

  // see if the list is empty
  if( ll->root == NULL ) {
    n = malloc(sizeof(Node));
    n->next = NULL;
    n->data = item;
    ll->root = n;
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
  if( ll->root == NULL )
    return(1);
  return(0);
}

/* Return a pointer to the top item in the list */
Shape *ll_peek( LinkedList *ll ) {
  if( ll->root == NULL )
    return(NULL);
  
  return(ll->root->data);
}

/* Sets the current iterator to the head of the list and 
   returns the data from the first node */
Shape *ll_head( LinkedList *ll ) {
  ll->current = ll->root;
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
  
  if( ll->root == NULL )
    return(NULL);
  
  n = ll->root;
  ll->root = ll->root->next;
  
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
      shape_free( p->data );
    free(p);
    p = q;
  }
  free( ll );	
  return;
}

