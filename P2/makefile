EXECUTABLE = p2

all:main

list.o: list.c list.h
	gcc -c list.c -g

listMem.o: listMem.c listMem.h
	gcc -c listMem.c -g

comandP0.o: comandP0.c comandP0.h
	gcc -c comandP0.c -g

comandP1.o: comandP1.c comandP1.h
	gcc -c comandP1.c -g

comandP2.o: comandP2.c comandP2.h
	gcc -c comandP2.c -g

funcion.o: funcion.c funcion.h
	gcc -c funcion.c -g

$(EXECUTABLE).o: $(EXECUTABLE).c list.h listMem.h funcion.h
	gcc -c $(EXECUTABLE).c -g

main: $(EXECUTABLE).o list.o listMem.o funcion.o comandP0.o comandP1.o comandP2.o
	gcc -o $(EXECUTABLE) $(EXECUTABLE).o list.o listMem.o funcion.o comandP0.o comandP1.o comandP2.o -g

clear:
	rm -f list.o listMem.o funcion.o comandP0.o comandP1.o comandP2.o $(EXECUTABLE).o $(EXECUTABLE)
