all: data

data: hash.o tree.o main.o
	gcc -g hash.o tree.o main.o -o data
    
hash.o: hash.c
	gcc -g -c hash.c

tree.o: tree.c
	gcc -g -c tree.c
    
main.o: main.c
	gcc -g -c main.c
    
clean:
	rm -rf *.o hash
	rm -rf *.o tree
	rm -rf *.o main
