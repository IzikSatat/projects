# makefile my_malloc

TARGET = my_malloc_run_test.out
CC = gcc
CFLAGS = -ansi -g3 -pedantic -Wall -Werror
OBJS = my_malloc.o my_malloc_test.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

my_malloc.o : my_malloc.c my_malloc.h
	$(CC) -c $(CFLAGS) my_malloc.c

my_malloc_test.o : my_malloc.c my_malloc_test.c my_malloc.h
	$(CC) -c $(CFLAGS) my_malloc_test.c

clean:
	rm -f $(TARGET) $(OBJS)
