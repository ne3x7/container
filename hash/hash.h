#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct Hash {
	MapMethods * m;
} Hash;

// <<-------------------------------------------- HashIterator methods --------------------------------------------->>

Iterator hash_iterator_first(Hash * h);
Iterator hash_iterator_last(Hash * h);
//Iterator * hash_iterator_forward(Hash * h, Iterator iter);
//Iterator * hash_iterator_backward(Hash * h, Iterator iter);
void * hash_iterator_get(Hash * h, Iterator iter);

// <<----------------------------------------------- Hash methods -------------------------------------------------->>

Hash * hash_create(int (* hash)(void * key), int size);
void hash_add(Hash * h, void * key, void * value);
void * hash_remove(Hash * h, void * key);
void hash_foreach(Hash * h, void (* func)(void * data, void * funcarg), void * arg);
void * hash_get(Hash * h, void * key);
void hash_destroy(Hash * h);

#ifdef __cplusplus
}
#endif