CC=gcc
CFLAGS=-g -Wall -std=c99
CClink=gcc
OBJS=stack.o student.o main.o
EXEC=prog.exe
RM=rm -f

$(EXEC): $(OBJS)
	$(CClink) $(OBJS) -o $(EXEC)

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

student.o: student.c student.h stack.h
	$(CC) $(CFLAGS) -c student.c

main.o: main.c student.h stack.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) $(OBJS) $(EXEC)




