#ifndef map_h
#define map_h

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct HashIterator {
	void * pos;
} HashIterator;

typedef struct TreeIterator {
	void * pos;
} TreeIterator;

typedef union Iterator {
	HashIterator hi;
	TreeIterator ti;
} Iterator;

typedef void * Map;

typedef struct MapMethods {
	Hash (* create)(int (* hash)(void * key), int size);
	void (* add)(Map map, void * key, void * value);
	void * (* remove)(Map map, void * key);
	void (* foreach)(Map map, void (* func)(void * data, void * funcarg), void * arg);
	int (* size)(Map map);
	void * (* get)(Map map, void * key);
	void (* destroy)(Map map);
} MapMethods;

#endif