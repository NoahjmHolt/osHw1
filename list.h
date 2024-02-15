//
// Created by noah holt on 2/14/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OSHW1_PROJ1_H
#define OSHW1_PROJ1_H

/* Declaring all the structs */
typedef struct Node node ;

 struct Node {
     char *item ;
     node *next ;
 };

typedef struct List{
     node *head;
 } list;

/* A l l o c a t e s p a c e f o r a new l i s t and s e t i t s head t o NULL.
  Returns t h e c r e a t e d l i s t i f s u c c e s s f u l , NULL o t h e r w i s e . */
list* create_list();

/*
 * Allocates a new node and copies the string from item to this node
 * (use malloc, strlen, and strncpy; or try strdup). Adds this new node
 *  to the end of the list linkList. Returns 0 if successful, non-zero otherwise
 */
int add_to_list(list* linkList);

/* Removes t h e head o f t h e l i s t l l , e x t r a c t s t h e s t r i n g s t o r e d i n t h e head ,
 * and returns a pointer to the string Also frees the removed head node. */
char* remove_from_list(list* linkList);

/*
 * Prints every string in each node of the list linkList, whith a new like
 * character at the end of each String
 */
void print_list(list* linkList);

/*
 * Flushes (clears) the entire list an re-initializes the list. The passed
 * pointer linkList should still point to a valid, empty list when this function
 * returns. Any memory allocated to store nodes in the list should be freed.
 */
void flush_list(list* linkList);

/*
 * De-allocates all data for the list. Ensure all memory allocated for list
 * linkList is freed, including any allocated strings and list linkList itself
 */
void free_list(list* linkList);

#endif //OSHW1_PROJ1_H
