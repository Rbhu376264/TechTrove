/** @file
 *  The prototypes needed to use our list implementation.
 */

#ifndef __LIST_H__
#define __LIST_H__

/* With #ifndef and #define, this header will be included only once, avoiding
   infinite loops if two .h files include each other. Clients of the library
   should include list.h and link against list.o, the compiled list.c */

/* A struct suitable for a linked list of strings: a list is a pointer to the
   first item. A `NULL` pointer is an empty list. */
struct _Item {
    struct _Item *next;
    char *value;
};

/**
 * A list item.
 *
 * This creates the alias `Item` for `struct _Item`.
 */
typedef struct _Item Item;

/**
 * Allocate and add an item to the head of the list.
 *
 * @return a pointer to the first item
 */
Item *list_prepend(Item *list, char *value);

/**
 * Deallocate the memory of each list item.
 */
void list_free(Item *list);

#endif /* __LIST_H__ */
