#include "iterator.h"
#include "list.h"

#include "stdio.h"

ListIterator * list_iterator_first(List * l) {
	ListIterator * iter = malloc(sizeof(ListIterator));
	iter->pos = l->head;
	return iter;
};
ListIterator * list_iterator_last(List * l) {
	ListIterator * iter = malloc(sizeof(ListIterator));
	ListElemet * a;

	if (l->head != NULL) {
	    a = l->head;
	    while (a != NULL)
		    a = a->next;
	    iter->pos = a;
    }
    else
    	iter->pos = l->head;

    return iter;
};
// ListIterator * list_iterator_find();
void list_iterator_destroy(ListIterator * li) {
	free(li->pos);
	free(li);
};
// void list_iterator_equals();
ListIterator * list_iterator_next(ListIterator * li) {
	ListElement * le = malloc(sizeof(ListElement));
	le = li->pos;
	if (le != NULL) {
		if (le->next != NULL)
			return le->next;
		else
			return NULL;
	}
	else
		return NULL;
};
ListIterator * list_iterator_prev(ListIterator * li) {
	ListElement * le = malloc(sizeof(ListElement));
	le = li->pos;
	if (le != NULL) {
		if (le->prev != NULL)
			return le->prev;
		else
			return NULL;
	}
	else
		return NULL;
};
void * list_iterator_get(ListIterator * li) {
	return li->pos->data;
};
// void list_iterator_replace();