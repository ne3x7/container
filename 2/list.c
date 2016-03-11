#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define LISTOBJ(l) (ListObject *) ((char *)l + sizeof(List))

ContainerMethods ListMethods = {
	list_insert_first,
	list_insert_last,
	list_delete_last,
	list_foreach,
	list_size,
	list_destroy,
	list_first,
	list_last,
	list_get
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct ListElement {
	void * prev;
	void * data;
	void * next;
} ListElement;

typedef struct ListObject {
	int size;
	ListElement * head;
	ListElement * tail;
} ListObject;

// <<-------------------------------------------- ListIterator methods -------------------------------------------->>

Iterator list_iterator_first(List * l) {
	Iterator iter;
	ListObject * lo = LISTOBJ(l);
	iter.li.pos = lo->head;
	return iter;
};
Iterator list_iterator_last(List * l) {
	Iterator iter;
	ListObject * lo = LISTOBJ(l);

	iter.li.pos = lo->tail;

    return iter;
};
int list_iterator_equals(Iterator a, Iterator b) {
	ListElement * one = a.li.pos;
	ListElement * two = b.li.pos;

	if (one->data == two->data)
		return 1;
	else
		return 0;
};
Iterator list_iterator_next(Iterator li) {
	Iterator res;
	ListElement * le = malloc(sizeof(ListElement));

	le = li.li.pos;

	if (le != NULL) {
		if (le->next != NULL) {
			res.li.pos = le->next;
			return res;
		}
		else
			exit(-1);
	}
	else
		exit(-1);
};
Iterator list_iterator_prev(Iterator li) {
	Iterator res;
	ListElement * le = malloc(sizeof(ListElement));
	le = li.li.pos;
	if (le != NULL) {
		if (le->prev != NULL) {
			res.li.pos = le->prev;
			return res;
		}
		else
			exit(-1);
	}
	else
		exit(-1);
};
void * list_iterator_get(Iterator li) {
	ListElement * a = li.li.pos;
	return a->data;
};

// <<------------------------------------------------ List methods ------------------------------------------------>>

List * list_create() {
	List * l = malloc(sizeof(List) + sizeof(ListObject));
	l->m = &ListMethods;
	ListObject * p = LISTOBJ(l);
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;
	return l;
};
void list_insert_first(List * l, void * data) {
	ListObject * lo = LISTOBJ(l);
	ListElement * old = lo->head;
	ListElement * head = malloc(sizeof(ListElement));

	head->prev = NULL;
    head->data = data;
    head->next = old;

    if (old != NULL) {
	    old->prev = head;
	}

	lo->head = head;
	lo->size++;

	if (lo->size == 1)
		lo->tail = head;
};
void list_insert_last(List * l, void * data) {
	ListObject * lo = LISTOBJ(l);
	ListElement * tail = malloc(sizeof(ListElement));
	ListElement * last = lo->tail;

	tail->prev = NULL;
	tail->data = data;
	tail->next = NULL;

	if (last != NULL) {
		tail->prev = last;
	    last->next = tail;
    }

    lo->tail = tail;
    lo->size++;

    if (lo->size == 1)
		lo->head = tail;
};
void * list_delete_last(List * l) {
	ListObject * lo = LISTOBJ(l);
	ListElement * last = lo->tail;

	if (lo->size == 0)
    	return NULL;

	ListElement * pre = last->prev;
    void * x;

    x = last->data;

    if (lo->size > 1) {
	    free(last);
	    pre->next = NULL;
	    lo->tail = pre;
	}
	else {
		free(last);
		lo->tail = NULL;
		lo->head = NULL;
	}

	lo->size--;
    return x;
};
void list_foreach(List * l, void (* func)(void * data, void * funcarg), void * arg) {
	Iterator first = l->m->first(l);
	Iterator last = l->m->last(l);
	Iterator iter = first;

	do {
		ListElement * le = iter.li.pos;
		void * data = le->data;

		func(data, arg);

		iter = list_iterator_next(iter); // поправить в list_iterator_next(&iter)
	} while (list_iterator_equals(iter, last));
};
int list_size(List * l) {
	ListObject * lo = LISTOBJ(l);
	return lo->size;
};
void list_destroy(List * l) {
	while (list_size(l) > 0) {
        list_delete_last(l);
    }

	free(l);
};
Iterator list_first(List * l) {
	return list_iterator_first(l);
};
Iterator list_last(List * l) {
	return list_iterator_last(l);
};
void * list_get(Iterator li) {
	return list_iterator_get(li);
};