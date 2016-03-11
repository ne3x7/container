#include "container.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct List {
	ContainerMethods * m;
} List;

// <<-------------------------------------------- ListIterator methods -------------------------------------------->>

Iterator list_iterator_first(List * l);
Iterator list_iterator_last(List * l);
// ListIterator list_iterator_find();
int list_iterator_equals(Iterator a, Iterator b);
Iterator list_iterator_next(Iterator li);
Iterator list_iterator_prev(Iterator li);
void * list_iterator_get(Iterator li);
// void list_iterator_replace();

// <<------------------------------------------------ List methods ------------------------------------------------>>

List * list_create();
// void list_insert();
void list_insert_first(List * l, void * data);
void list_insert_last(List * l, void * data);
void * list_delete_last(List * l);
void list_foreach(List * l, void (* func)(void * data, void * funcarg), void * arg);
int list_size(List * l);
// Data list_find();
void list_destroy(List * l);
Iterator list_first(List * l);
Iterator list_last(List * l);
void * list_get(Iterator li);

#ifdef __cplusplus
}
#endif