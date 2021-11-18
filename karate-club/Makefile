#Makefile#

all: karate-club clean
karate-club: karate-club.o readgml.o
	gcc -o karate-club karate-club.o readgml.o -Wall -std=c99
readgml.o: readgml.c
	gcc readgml.c -o readgml.o -c -Wall -std=c99
karate-club.o: karate-club.c
	gcc karate-club.c -o karate-club.o -c -Wall -std=c99
clean:
	rm -rf *.o
