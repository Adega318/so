.SUFIXES: .o .c
.C.o:
		$(CC) -c $(CFLAGS) $<
#Macros
CC=gcc
CFLAGS= -Wall -g
SRC= p1.c funcion.h funcion.c 
OBJ= p1.o funcion.o

#reglas expliicitas
all: $(OBJ)
		$(CC) $(CFLAGS) -o p1 $(OBJ)
clear:
		$(RM) $(OBJ) p1
debugg:
		gdb p1

#reglas implicitas
funcion.o: funcion.h funcion.c 
p1.o: p1.c funcion.c

