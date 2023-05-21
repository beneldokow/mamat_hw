CC=gcc
CFLAGS=-Wall -g -std=c99 -fpic
CLINK=gcc

libgrades.so: grades.o
	$(CLINK) -shared -o libgrades.so grades.o -llinked-list -L.

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c

clean:
	rm -f *.o *.so
