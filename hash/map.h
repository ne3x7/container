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

typedef struct Map {
	struct MapMethods * m;
} Map;

typedef struct MapMethods {
	void (* add)(Map * map, void * key, void * value);
	void * (* remove)(Map * map, void * key);
	void (* foreach)(Map * map, void (* func)(void * data, void * funcarg), void * arg);
	void * (* get)(Map * map, void * key);
	void (* destroy)(Map * map);
} MapMethods;

#endif