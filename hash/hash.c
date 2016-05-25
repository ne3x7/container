#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "map.h"

#define HASHOBJ(hash) (HashObject *) ((char *)hash + sizeof(Hash))

MapMethods HashMethods = {
	hash_add,
	hash_remove,
	hash_get,
	hash_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct HashObject { // у каждого экземпляра map свой массив
	int (* hash)(void * data); // хэш-функция
	struct HashArrayElement ** array;
	int size;
} HashObject;

typedef struct HashArrayElement {
	struct HashListElement * head;
} HashArrayElement;

typedef struct HashListElement { // элементы цепочки имеют ключ и значение
	struct HashListElement * previous;
	void * key;
	void * value;
	struct HashListElement * next;
} HashListElement;

// <<-------------------------------------------- HashIterator methods -------------------------------------------->>

Iterator hash_iterator_first(Hash * h) {
	HashIterator iter;
	Iterator res;

	HashObject * ho = HASHOBJ(h);
	HashArrayElement * hae = ho->array[0];
	iter.pos = hae->head;
	res.hi = iter;

	return res;
};
Iterator hash_iterator_last(Hash * h) {
	HashIterator iter;
	Iterator res;

	HashObject * ho = HASHOBJ(h);
	HashArrayElement * hae = ho->array[ho->size];
	HashListElement * head = hae->head;

	if (head != NULL) {
		do {
			head = head->next;
		} while (head != NULL);

		iter.pos = head;
	}
	else
		iter.pos = head->next;

	res.hi = iter;
	return res;
};
//Iterator * hash_iterator_forward(Hash * h, Iterator iter);
//Iterator * hash_iterator_backward(Hash * h, Iterator iter);
void * hash_iterator_get(Hash * h, Iterator iter) {
	HashListElement * hle = iter.hi.pos;
	return hle->value;
};

// <<----------------------------------------------- Hash methods ------------------------------------------------->>

Hash * hash_create(int (* hash)(void * key), int size) { // пока так
	int i = 0;
	Hash * h = malloc(sizeof(Hash) + sizeof(HashObject));
	h->m = &HashMethods;
	HashObject * ho = HASHOBJ(h);
	ho->hash = hash;
	ho->size = size;
	if (size > 0) {
		ho->array = malloc(size * sizeof(HashArrayElement *));
		for (i = 0; i < size; i++)
			ho->array[i] = malloc(sizeof(HashArrayElement));
		for (i = 0; i < size; i++) {
			HashArrayElement * item = ho->array[i];
			item->head = NULL;
		}
	}
	return h;
};
void hash_add(Hash * h, void * key, void * value) {
	HashObject * ho = HASHOBJ(h);
	int index = ho->hash(key);
	HashArrayElement * hae = ho->array[index];

	if (hae->head != NULL) {
		HashListElement * head = hae->head;
		while (head->next != NULL)
			head = head->next;
		HashListElement * new_node = malloc(sizeof(HashListElement));

		new_node->previous = head;
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;

		head->next = new_node;
	}
	else {
		HashListElement * head = malloc(sizeof(HashListElement));
		head->previous = NULL;
		head->key = key;
		head->value = value;
		head->next = NULL;
		hae->head = head;
	}
};
void * hash_remove(Hash * h, void * key) {
	HashObject * ho = HASHOBJ(h);
	int index = ho->hash(key);
	void * vtr = NULL;
	HashArrayElement * hae = ho->array[index];

	if (hae->head != NULL) {
		HashListElement * head = hae->head;
		HashListElement * prev = NULL;

		do {
			if (head->key == key) {
				if (prev != NULL) {
					prev->next = head->next;
					head->next->previous = prev;
				}
				else {
					head->next->previous = NULL;
					hae->head = head->next;
				}

				vtr = head->value;
				HashListElement * tmp = head->next;
				free(head);
				head = tmp;

				break;
			}
			else {
				prev = head;
				head = head->next;
			}
		} while (head != NULL);

		return vtr;
	}
	else
		return vtr;
};
// void hash_foreach(Map * map, void (* func)(void * data, void * funcarg), void * arg);
void * hash_get(Hash * h, void * key) {
	HashObject * ho = HASHOBJ(h);
	int index = ho->hash(key);
	HashArrayElement * hae = ho->array[index];

	if (hae->head != NULL) {
		HashListElement * head = hae->head;

		do {
			if (head->key == key)
				return head->value;

			head = head->next;
		} while (head != NULL);

		return NULL;
	}
	else
		return NULL;
};
void hash_destroyer(HashListElement * hle) {
	if (hle->next != NULL)
		hash_destroyer(hle->next);
	free(hle);
};
void hash_destroy(Hash * h) {
	int i;
	HashObject * ho = HASHOBJ(h);
	for (i = 0; i < ho->size; i++) { // для всех цепочек
		HashArrayElement * hae = ho->array[i];
		if (hae->head != NULL) {
			HashListElement * head = hae->head;
			hash_destroyer(head);
		}

		free(ho->array[i]);
	}

	free(ho->array);
	free(h);
};