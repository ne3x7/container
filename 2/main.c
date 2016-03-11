#include <stdio.h>
#include <stdlib.h>

#include "list.h"
// #include "array.h"

int main(int argc, void * argv[]) {
	List * l = list_create();

	l->m->insert_last(l, "one");
	l->m->insert_last(l, "two");
	l->m->insert_last(l, "three");

	Iterator first = l->m->first(l);
	Iterator second = list_iterator_next(first);
	Iterator last = l->m->last(l);

	void * str = l->m->get(first);
	printf("%s\n", (char *)str);
	str = l->m->get(second);
	printf("%s\n", (char *)str);
	str = l->m->get(last);
	printf("%s\n-----------------------\n", (char *)str);

	str = l->m->delete_last(l);
	printf("%s\n", (char *)str);
	str = l->m->delete_last(l);
	printf("%s\n", (char *)str);
	str = l->m->delete_last(l);
	printf("%s\n-----------------------\n", (char *)str);

	printf("Size = %d\n", l->m->size(l));

	l->m->insert_last(l, "new one");

	printf("Size = %d\n", l->m->size(l));

	first = l->m->first(l);
	str = l->m->get(first);
	printf("%s\n", (char *)str);

	l->m->destroy(l);

	return 0;
}