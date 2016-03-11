#include "container.h"

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct Array {
	ContainerMethods * m;
	int size;
	void ** array;
} Array;

typedef struct ArrayIterator {
	int pos;
} ArrayIterator;

// <<------------------------------------------- ArrayIterator methods -------------------------------------------->>

ArrayIterator * array_iterator_first(Array * arr);
ArrayIterator * array_iterator_last(Array * arr);
// ArrayIterator array_iterator_find();
void array_iterator_destroy(ArrayIterator * ai);
// void array_iterator_equals();
ArrayIterator * array_iterator_next(Array * arr, ArrayIterator * ai);
ArrayIterator * array_iterator_prev(Array * arr, ArrayIterator * ai);
void * array_iterator_get(Array * arr, ArrayIterator * ai);
// void array_iterator_replace();

// <<------------------------------------------------ Array methods ----------------------------------------------->>

Array * array_create();
void array_insert(Array * arr, void * data, int pos);
void array_insert_first(Array * arr, void * data);
void array_insert_last(Array * arr, void * ata);
void * array_delete_first(Array * arr);
void * array_delete_last(Array * arr);
// void * array_find();
void array_destroy(Array * arr);
ArrayIterator * array_first(Array * arr);
ArrayIterator * array_last(Array * arr);
void * array_get(Array * arr, ArrayIterator * ai);