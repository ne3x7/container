typedef struct ListIterator {
	void * pos;
} ListIterator;

typedef struct ArrayIterator {
	int pos;
} ArrayIterator;

#ifndef container_h
#define container_h

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef union Iterator {
	ListIterator li;
	ArrayIterator ai;
} Iterator;

typedef void * Container;

typedef struct ContainerMethods {
	void (* insert_first)(Container c, void * data);
	void (* insert_last)(Container c, void * data);
	void * (* delete_last)(Container c);
	void (* foreach)(Container c, void (* func)(void * data, void * funcarg), void * arg);
	int (* size)(Container c);
	void (* destroy)(Container c);
	Iterator (* first)(Container c); // returns Iterator
	Iterator (* last)(Container c);  // returns Iterator
	void * (* get)(Iterator i); 		 // accepts Iterator
} ContainerMethods;

// typedef struct ListMethods { } ListMethods;

// typedef struct ArrayMethods { } ArrayMethods;

#endif