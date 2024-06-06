# Define the compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES =

# Define library paths in addition to /usr/lib
LFLAGS =

# Define any libraries to link into executable
LIBS =

# Define the object files
OBJS = main.o helper.o

# Define the executable file 
EXEC = main

# The default target
all: $(EXEC)

# Rule to link the object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Rule to compile main.c to main.o
main.o: main.c helper.h
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

# Rule to compile helper.c to helper.o
helper.o: helper.c helper.h
	$(CC) $(CFLAGS) $(INCLUDES) -c helper.c

# Rule to clean the directory
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
