#include "hash.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct Map {
	HashMethods * m;
} Map;

// <<-------------------------------------------- MapIterator methods --------------------------------------------->>

Iterator map_iterator_first(Map * m);
Iterator map_iterator_last(Map * m);
Iterator * map_iterator_forward(Map * m, Iterator iter);
Iterator * map_iterator_backward(Map * m, Iterator iter);

// <<------------------------------------------------ Map methods ------------------------------------------------->>

Map * map_create(int (* hash)(void * key), int size);
void map_add(Map * m, void * key, void * value);
void * map_remove(Map * m, void * key);
void foreach(Map * m, void (* func)(void * data, void * funcarg), void * arg);
int map_size(Map * m);
void * map_at(Map * m, void * key);
void map_destroy(Map * m);

#ifdef __cplusplus
}
#endif