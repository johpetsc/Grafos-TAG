#Makefile#

all: proj1 clean
proj1: proj1.o readgml.o
	gcc -o proj1 proj1.o readgml.o -Wall -std=c99
readgml.o: readgml.c
	gcc readgml.c -o readgml.o -c -Wall -std=c99
proj1.o: proj1.c
	gcc proj1.c -o proj1.o -c -Wall -std=c99
clean:
	rm -rf *.o
