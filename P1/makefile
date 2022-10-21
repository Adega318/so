EXECUTABLE = p1

all:main

list.o: list.c list.h
	gcc -c list.c -g

comandP0.o: comandP0.c comandP0.h
	gcc -c comandP0.c -g

comandP1.o: comandP1.c comandP1.h
	gcc -c comandP1.c -g

funcion.o: funcion.c funcion.h
	gcc -c funcion.c -g

$(EXECUTABLE).o: $(EXECUTABLE).c list.h funcion.h
	gcc -c $(EXECUTABLE).c -g

main: $(EXECUTABLE).o list.o funcion.o comandP0.o comandP1.o
	gcc -o $(EXECUTABLE) $(EXECUTABLE).o list.o funcion.o comandP0.o comandP1.o -g

clear:
	rm -f list.o funcion.o comandP0.o comandP1.o $(EXECUTABLE).o $(EXECUTABLE)
