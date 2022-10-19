.SUFIXES: .o .c
.C.o:
		$(CC) -c $(CFLAGS) $<
#Macros
CC=gcc
CFLAGS= -Wall -g
SRC= p0.c funcion.h funcion.c 
OBJ= p0.o funcion.o

#reglas expliicitas
all: $(OBJ)
		$(CC) $(CFLAGS) -o p0 $(OBJ)
clear:
		$(RM) $(OBJ) p0
debugg:
		gdb p0

#reglas implicitas
funcion.o: funcion.h funcion.c 
p0.o: p0.c funcion.c

