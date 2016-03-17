#ifndef container_h
#define container_h

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct MapIterator {
	void * key;
} MapIterator;

typedef struct TreeIterator {
	int pos;
} TreeIterator;

typedef union Iterator {
	MapIterator mi;
	TreeIterator ti;
} Iterator;

typedef void * Hash;

typedef struct HashMethods {
	Hash (* create)(int size);
	void (* add)(Hash hash, void * key, void * value);
	void * (* remove)(Hash hash, void * key);
	void (* foreach)(Hash hash, void (* func)(void * data, void * funcarg), void * arg);
	int (* size)(Hash hash);
	void * (* at)(Hash hash, void * key);
	void (* destroy)(Hash hash);
} HashMethods;

#endif