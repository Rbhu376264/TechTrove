/** @file
 *  A simple example of C program.
 */

/* #include <..> inserts a system header like /usr/include/stdio.h */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/* #include ".." inserts a custom header list.h from current dir */
#include "list.h"

// Single-line comments are allowed since C99!

// Define a constant (SECRET_NUMBER replaced with 42 by the preprocessor)
#define SECRET_NUMBER 5

// Define a macro (all parentheses are necessary, try to remove them!)
#define ONE_PLUS_TWICE(x) (1+2*(x))

// This prototype allows us to use `print_args()` in `main` and define it after.
// `static` functions can be called only from this file (a "compilation unit").
static void print_args(int argc, char **argv);

/**
 * Main function of the program.
 *
 * The main function of a C program has a special signature.
 * We're using the [DoxyGen](http://www.doxygen.nl/manual/docblocks.html)
 * syntax for comments. Run `make docs` to regenerate the documentation.
 *
 * @param argc number of command-line arguments
 * @param argv array of strings, which are `char *` in C
 * @return exit code (nonzero in case of error, as usual in C)
 */
int main(int argc, char **argv) {
    // call a static function (available only in this file, like private in C++)
    print_args(argc, argv);

    // use the constant and macro: prints 2*(1+2*(5+1)) == 26
    fprintf(stderr, "Macro example: %d\n", 2*ONE_PLUS_TWICE(SECRET_NUMBER+1));

    // CTRL+d is standard in Unix to signal the end of a stream
    fprintf(stderr, "Type a name and press ENTER to greet a user\n");
    fprintf(stderr, "(CTRL-d will terminate the program)\n");
    fprintf(stderr, "(An empty line will cause an error)\n");

    char *line = NULL;   // pointer to read buffer
    size_t len = 0;      // current size of read buffer
                         // size_t is for sizes of objects (>= 0)
    ssize_t nread;       // characters of the line (including newline)
                         // ssize_t is for byte counts or negative errors

    // stdin is the standard input stream (try ./hello < name.txt)
    // getline() allocates and reallocates the read buffer as needed
    // (you must free it at the end) and modifies line/len variables
     while ((nread = getline(&line, &len, stdin)) != -1) {
        if (nread == 1) {
            // empty line (read just \n): free buffer and quit with error
            // non-zero return codes represent errors
            free(line);
            return 1;
        } else {
            // at the end of the string, change \n\0 to \0\0 to drop newline
            line[nread-1] = '\0';
            printf("Hello %s!\n", line);
        }
    }

    // success: the stream ended without empty lines, return 0
    free(line);
    return 0;
}

/**
 * Print the command-line arguments to stderr.
 *
 * @param argc number of arguments
 * @param argv array of strings
 */
static void print_args(int argc, char **argv) {
    // print to stderr, which is a stream separate from stdin
    fprintf(stderr, "Arguments (%d in total): ", argc);

    /* for fun:
       - add them to the head of a linked list
       - Item and list_prepend are defined in list.h
       - variables can be defined anywhere since C99
    */
    Item *list = NULL;
    for (int i = 0; i < argc; i++) {
        fprintf(stderr, "[%d: %s] ", i, argv[i]);
        list = list_prepend(list, argv[i]);
    }
    fprintf(stderr, "\n");

    // scan the list and print the elements again
    fprintf(stderr, "Arguments in reverse order: ");
    for (Item *it = list; it != NULL; it = it->next) {
        fprintf(stderr, "[%s] ", it->value);
    }
    fprintf(stderr, "\n");

    // release the memory of the list
    list_free(list);
}
