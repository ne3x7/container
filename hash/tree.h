#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct Tree {
	MapMethods * m;
} Tree;

// <<-------------------------------------------- TreeIterator methods --------------------------------------------->>

//Iterator tree_iterator_first(Tree * t);
//Iterator tree_iterator_last(Tree * t);
//Iterator * tree_iterator_forward(Tree * t, Iterator iter);
//Iterator * tree_iterator_backward(Tree * t, Iterator iter);
//void * tree_iterator_get(Tree * t, Iterator iter);

// <<------------------------------------------------ Tree methods ------------------------------------------------->>

Tree * tree_create(int (* hash)(void * key));
void tree_add(Tree * t, void * key, void * value);
void * tree_remove(Tree * t, void * key);
void tree_foreach(Tree * t, void (* func)(void * data, void * funcarg), void * arg);
void * tree_get(Tree * t, void * key);
void tree_destroy(Tree * t);
// void tree_trace(Tree * t);

#ifdef __cplusplus
}
#endif