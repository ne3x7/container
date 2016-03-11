#include "list.h"

ListIterator * list_iterator_first(List * l);
ListIterator * list_iterator_last(List * l);
// ListIterator list_iterator_find();
void list_iterator_destroy(ListIterator * li);
// void list_iterator_equals();
ListIterator * list_iterator_next(ListIterator * li);
ListIterator * list_iterator_prev(ListIterator * li);
void * list_iterator_get(ListIterator * li);
// void list_iterator_replace();