#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int MAPSIZE = 10;

int hfunc(void * key) {
	return *((int *) key) % MAPSIZE;
}

int main(int argc, char const *argv[])
{
	Map * map = hash_create(hfunc, MAPSIZE);
	printf("Created successfully\n");
	int one = 1;
	int two = 2;
	int three = 3;

	map->m->add(map, &one, "one");
	printf("Added 1 successfully\n");
	map->m->add(map, &two, "two");
	printf("Added 2 successfully\n");
	map->m->add(map, &three, "three");
	printf("Added 3 successfully\n");

	map->m->destroy(map);
	printf("Destroyed successfully\n");
	return 0;
}