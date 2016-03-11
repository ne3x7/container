#include <stdio.h>
#include <stdlib.h>

#include "list.h"
// #include "array.h"

int main(int argc, void * argv[]) {
	List * l = list_create();
	l->m->insert_last(l, "one");
	Iterator iter = l->m->first(l);
	void * str = l->m->get(iter);
	printf("%s\n", (char *)str);
	/* 
	void * str;
	
	list_insert_last(l, "one");
	list_insert_last(l, "two");
	list_insert_last(l, "three");

	ListIterator * first = list_iterator_first(l);
	ListIterator * last = list_iterator_last(l);
	ListIterator * second = list_iterator_next(first);

	str = list_get(first);
	printf("%s\n", (char *)str);
	str = list_get(second);
	printf("%s\n", (char *)str);
	str = list_get(last);
	printf("%s\n", (char *)str);

	list_iterator_destroy(first);
	list_iterator_destroy(second);
	list_iterator_destroy(last);
	list_destroy(l);

	Array * arr = array_create();

	array_insert_last(arr, "one");
	array_insert_last(arr, "two");
	array_insert_last(arr, "three");

	ArrayIterator * afirst = array_iterator_first(arr);
	ArrayIterator * alast = array_iterator_last(arr);
	ArrayIterator * asecond = array_iterator_next(arr, afirst);

	str = array_get(arr, afirst);
	printf("%s\n", (char *)str);
	str = array_get(arr, asecond);
	printf("%s\n", (char *)str);
	str = array_get(arr, alast);
	printf("%s\n", (char *)str);

	array_iterator_destroy(afirst);
	array_iterator_destroy(asecond);
	array_iterator_destroy(alast);
	array_destroy(arr);
	*/
	return 0;
}