#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct Hash {
	MapMethods * m;
} Hash;

// <<-------------------------------------------- MapIterator methods --------------------------------------------->>

Iterator hash_iterator_first(Hash * h);
Iterator hash_iterator_last(Hash * h);
Iterator * hash_iterator_forward(Hash * h, Iterator iter);
Iterator * hash__iterator_backward(Hash * h, Iterator iter);

// <<------------------------------------------------ Map methods ------------------------------------------------->>

Hash * hash_create(int (* hash)(void * key), int size);
void hash_add(Hash * h, void * key, void * value);
void * hash_remove(Hash * h, void * key);
// void hash_foreach(Hash * h, void (* func)(void * data, void * funcarg), void * arg);
int hash_size(Hash * h);
void * hash_get(Hash * h, void * key);
void hash_destroy(Hash * h);

#ifdef __cplusplus
}
#endif