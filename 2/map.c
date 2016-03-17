#include <stdio.h>
#include <stdlib.h>

#include "map.h"

#define MAPOBJ(map) (MapObject *) ((char *)map + sizeof(Map))

HashMethods MapMethods = {
	map_create,
	map_add,
	map_remove,
	foreach,
	map_size,
	map_at,
	map_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct MapObject { // у каждого экземпляра map свой массив
	MapArrayElement ** array; // массив указателей
	int size;
} MapObject;

typedef struct MapArrayElement { // у каждого элемента массива есть хэш и цепочка
	void * hash;
	MapListElement ** chain; // массив указателей
} MapArrayElement;

typedef struct MapListElement { // элементы цепочки имеют ключ и значение
	MapListElement * previous;
	void * key;
	void * value;
	MapListElement * next;
} MapElement;

// <<-------------------------------------------- MapIterator methods --------------------------------------------->>

Iterator map_iterator_first(Map * m);
Iterator map_iterator_last(Map * m);
Iterator * map_iterator_forward(Map * m, Iterator iter);
Iterator * map_iterator_backward(Map * m, Iterator iter);

// <<------------------------------------------------ Map methods ------------------------------------------------->>

Map * map_create(int size) { // пока так
	Map * map = malloc(sizeof(Map) + sizeof(MapObject));
	map->m = MapMethods;
	MapObject * mo = MAPOBJ(map);
	mo->size = size;
	mo->array = malloc(size * sizeof(MapArrayElement));
};
void map_add(Map * map, void * key, void * value);
void * map_remove(Map * map, void * key);
void foreach(Map * map, void (* func)(void * data, void * funcarg), void * arg);
int map_size(Map * map);
void * map_at(Map * map, void * key);
void map_destroy(Map * map);