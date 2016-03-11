#include <stdio.h>
#include <stdlib.h>

#include "array.h"

// <<------------------------------------------- ArrayIterator methods -------------------------------------------->>

ArrayIterator * array_iterator_first(Array * arr) {
	ArrayIterator * iter = malloc(sizeof(ArrayIterator));
	iter->pos = 0;
	return iter;
};
ArrayIterator * array_iterator_last(Array * arr) {
	ArrayIterator * iter = malloc(sizeof(ArrayIterator));
	iter->pos = arr->size - 1;
	return iter;
};
// ArrayIterator array_iterator_find();
void array_iterator_destroy(ArrayIterator * ai) {
	free(ai);
};
// void array_iterator_equals();
ArrayIterator * array_iterator_next(Array * arr, ArrayIterator * ai) {
	ArrayIterator * iter = malloc(sizeof(ArrayIterator));
	iter->pos = (ai->pos + 1) % arr->size;
	return iter;
};
ArrayIterator * array_iterator_prev(Array * arr, ArrayIterator * ai) {
	ArrayIterator * iter = malloc(sizeof(ArrayIterator));
	iter->pos = ai->pos - 1;
	if (iter->pos < 0)
		iter->pos = arr->size - iter->pos;
	return iter;
};
void * array_iterator_get(Array * arr, ArrayIterator * ai) {
	void ** ptr = arr->array;
	void * data = ptr[ai->pos];
	return data;
};
// void array_iterator_replace();

// <<------------------------------------------------ Array methods ----------------------------------------------->>

Array * array_create() {
	Array * arr = malloc(sizeof(Array));
	arr->size = 0;
	arr->array = malloc(sizeof(void **));
};
void array_insert(Array * arr, void * data, int pos) {
	int i;
	void ** ptr = arr->array;

	arr->size += 1;
	ptr = realloc(ptr, arr->size);

	for (i = arr->size - 1; i > pos; i--)
		ptr[i] = ptr[i - 1];

	ptr[pos] = data;
};
void array_insert_first(Array * arr, void * data) {
	int i;
	void ** ptr = arr->array;

	arr->size += 1;
	ptr = realloc(ptr, arr->size);

	for (i = arr->size - 1; i > 0; i--)
		ptr[i] = ptr[i - 1];

	ptr[0] = data;
};
void array_insert_last(Array * arr, void * data) {
	void ** ptr = arr->array;

	arr->size += 1;
	ptr = realloc(ptr, arr->size);

	ptr[arr->size - 1] = data;
};
void * array_delete_first(Array * arr) {
	int i;
	void ** ptr = arr->array;
	void * data = ptr[0];

	for (i = 0; i < arr->size - 1; i++)
		ptr[i] = ptr[i + 1];

	arr->size -= 1;
	ptr = realloc(ptr, arr->size);

	return data;
};
void * array_delete_last(Array * arr) {
	void ** ptr = arr->array;
	void * data = ptr[arr->size - 1];

	arr->size -= 1;
	ptr = realloc(ptr, arr->size);

	return data;
};
// void * array_find();
void array_destroy(Array * arr) {
	int i;
	void ** ptr = arr->array;
	/*
	for (i = 0; i < arr->size; i++)
		free(ptr[i]);
	*/
	free(ptr);
};
ArrayIterator * array_first(Array * arr) {
	return array_iterator_first(arr);
};
ArrayIterator * array_last(Array * arr) {
	return array_iterator_last(arr);
};
void * array_get(Array * arr, ArrayIterator * ai) {
	return array_iterator_get(arr, ai);
};