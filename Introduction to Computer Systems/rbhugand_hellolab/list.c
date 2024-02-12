/** @file
 *  The implementation of our list functions.
 */

#include <stdlib.h>
#include "list.h"

/* list.c includes its own header list.h to make sure that:
   - functions can be defined in any order inside list.c
   - function signatures implemented in list.c match those
     that clients consume from list.h                       */

Item *list_prepend(Item *list, char *value) {
    // allocate a new item dynamically, no need to cast
    Item *item = malloc(sizeof(Item));
    // set the value and pointer to next
    item->value = value;
    item->next = list;
    // return the new head of the list
    return item;
}

void list_free(Item *list) {
    while (list != NULL) {
        // save a copy of the pointer to the next item
        Item *next = list->next;
        // release the memory of this item
        free(list);
        // move to the next one
        list = next;
    }
}
