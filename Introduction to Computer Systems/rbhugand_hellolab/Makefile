# Add flags to those already defined by the user
# -Wall -Wextra add more warnings (a good thing)
# -std=c17 selects the C standard from 2017
# -D_POSIX_C_SOURCE=200809L enables POSIX.1-2008 features (getline in stdio.h)
# -MMD -MP generate .d files so that we know which .h are included in each .c
# -g generates symbols for debugging
CFLAGS += -Wall -Wextra -std=c17 -D_POSIX_C_SOURCE=200809L -MMD -MP -g

# The executable file to create
OUT = hello
# Our source files: only .c, no .h (they are found by the preprocessor)
SRC = hello.c list.c
# Object files have the same name as .c but with .o
OBJ = $(SRC:.c=.o)

# Phony targets don't have a file that has to be more recent than
# its dependencies. They are always run.
.PHONY: all docs clean

# Default goal (the one we run with just `make`)
.DEFAULT_GOAL := all

# Our default goal is to rebuild `hello` every time some .h or .c changes
all: $(OUT)

# Each .o depends on its .c
#   CC is an implicit variable in Makefiles equal to cc, a symlink to gcc
#   `$<` is the first dependency, the .c file
#   `$@` is the target, the .o file
#   so, we're compiling as `gcc -c file.c -o file.o` for each .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include rules from .d files produced by GCC with the -MMD -MP flags
# These allow us to the track dependencies of .o on .h (very important)
-include $(OBJ:.o=.d)

# hello depends on all of the .o
#   we need to link together all the .o files into an executable
#   `$^` is $(OBJ), all the dependencies of this rule
#   `$@` is the target, the `hello` file
#   so, we're compiling as `gcc hello.o list.o -o hello` (plus flags)
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Generate docs
docs:
	doxygen docs/Doxyfile

# Delete all the files produced by compilation or ignored by git
clean:
	rm -rf *.o *.d $(OUT) docs/html
	git clean -xdf
