all: data

data: hash.o main.o
	gcc -g hash.o main.o -o data
    
hash.o: hash.c
	gcc -g -c hash.c
    
main.o: main.c
	gcc -g -c main.c
    
clean:
	rm -rf *.o hash
	rm -rf *.o main
