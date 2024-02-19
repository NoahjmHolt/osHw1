//
// Created by noah holt on 2/14/24.
//
#include "list.h"

/*
 * Prints every string in each node of the list linkList, whith a new like
 * character at the end of each String
 */
void print_list(list* linkList){

    //set placeholder
    Node element = linkList->head;

    //print while still has next
    while (element->next != NULL){
        printf(element.item, '\n');
        element = element.next;
    } // print all except last string

    //print last thing
    printf(element.item, '\n');

}

/*
 * Flushes (clears) the entire list an re-initializes the list. The passed
 * pointer linkList should still point to a valid, empty list when this function
 * returns. Any memory allocated to store nodes in the list should be freed.
 */
void flush_list(list* linkList){

    //set placeholder
    Node element = linkList->head;

    //set first element to no words and free end of list.
    while (element.next != NULL){
        linkList->head = element.next;
        free(element.next);
    } // This doesn't seem right but can talk with group member later.

    free(linkList->head);

}

/*
 * De-allocates all data for the list. Ensure all memory allocated for list
 * linkList is freed, including any allocated strings and list linkList itself
 */
void free_list(list* linkList){

    //set placeholder
    Node element = linkList->head;

    //set first element to no words and free end of list.
    while (element.next != NULL){
        linkList->head = element.next;
        free(element.next);
    } // This doesn't seem right but can talk with group member later.

    free(linkList->head);
    free(linkList);

}
