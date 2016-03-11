all: data

data: list.o main.o
	gcc -g list.o main.o -o data
    
list.o: list.c
	gcc -g -c list.c
    
main.o: main.c
	gcc -g -c main.c
    
clean:
	rm -rf *.o list
	rm -rf *.o main
