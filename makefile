all: main.o avl.o conjunto.o 
	gcc main.o avl.o conjunto.o  -o main -std=c99 -Wall

main.o:
	gcc -c main.c

avl.o:
	gcc -c avl.c

conjunto.o:
	gcc -c conjunto.c 

run:all
	./main
	
clean:
	rm -rf *.o main