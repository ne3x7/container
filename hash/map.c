#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define HASHOBJ(hash) (HashObject *) ((char *)hash + sizeof(Hash))

HashMethods HashMethods = {
	hash_create,
	hash_add,
	hash_remove,
	hash_foreach,
	hash_size,
	hash_at,
	hash_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct HashObject { // у каждого экземпляра map свой массив
	int (* hash)(void * data); // хэш-функция
	HashArrayElement ** array; // массив указателей
	int size;
	int count;
} HashObject;

typedef struct HashArrayElement { // у каждого элемента массива есть хэш и цепочка
	int chain_len; // убрать
	HashListElement * head; // можно хранить только голову и работать как со списком
} HashArrayElement;

typedef struct HashListElement { // элементы цепочки имеют ключ и значение
	HashListElement * previous;
	void * key;
	void * value;
	HashListElement * next;
} HashElement;

// <<-------------------------------------------- MapIterator methods --------------------------------------------->>

Iterator hash_iterator_first(Map * m);
Iterator hash_iterator_last(Map * m);
Iterator * hash_iterator_forward(Map * m, Iterator iter);
Iterator * hash_iterator_backward(Map * m, Iterator iter);
void * hash_iterator_get(Map * m, Iterator iter);

// <<------------------------------------------------ Map methods ------------------------------------------------->>

Map * hash_create(int (* hash)(void * key, void * value), int size) { // пока так
	Map * map = malloc(sizeof(Map) + sizeof(MapObject));
	map->m = MapMethods;
	MapObject * mo = MAPOBJ(map);
	mo->hash = hash;
	mo->size = size;
	mo->array = malloc(size * sizeof(MapArrayElement));
	return map;
};
void hash_add(Map * map, void * key, void * value) {
	MapObject * mo = MAPOBJ(map);
	int index = mo->hash(key);
	MapArrayElement * mae = mo->array[index];

	if (mae->head != NULL) {
		MapListElement * head = mae->head;
		while (head->next != NULL)
			head = head->next;
		MapListElement * new_node = malloc(sizeof(MapListElement));

		new_node->previous = head;
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;

		head->next = new_node;
	}
	else {
		MapListElement * head = malloc(sizeof(MapListElement));
		head->previous = NULL;
		head->key = key;
		head->value = value;
		head->next = NULL;
		mae->head = head;
	}

	mae->chain_len++;
};
void * hash_remove(Map * map, void * key) {
	MapObject * mo = MAPOBJ(map);
	int index = mo->hash(key);
	void * vtr;
	MapArrayElement * mae = mo->array[index];

	if (mae->head != NULL) {
		MapListElement * head = mae->head;

		while (head->next != NULL) {
			if (head->key == key) {
				vtr = head->value;

				// magic с убиранием из середины списка

				break;
			}
			head = head->next;
		}

		if (head->key == key) {
			vtr = head->value;

			// magic с убиранием из конца списка
		}
		else {
			// выдать ошибку
			exit(-1);
		}

		return vtr;
	}
	else {
		// выдать ошибку
		exit(-1);
	}
};
// void hash_foreach(Map * map, void (* func)(void * data, void * funcarg), void * arg);
int hash_size(Map * map) {
	// пройтись по всем
};
void * hash_at(Map * map, void * key) {
	MapObject * mo = MAPOBJ(map);
	int index = mo->hash(key);
	MapArrayElement * mae = mo->array[index];

	if (mae->head != NULL) {
		MapListElement * head = mae->head;

		if (head->key == key)
			return head->value;
		while (head->next != NULL) {
			head = head->next;
			if (head->key == key)
				return head->value;
		}

		if (head->key == key)
			return head->value;
		else {
			// выдать ошибку
			exit(-1);
		}
	}
	else {
		// выдать ошибку
		exit(-1);
	}
};
void hash_destroy(Map * map) {
	MapObject * mo = MAPOBJ(map);
	for (i = 0; i < mo->size; i++) { // для всех цепочек
		MapArrayElement * mae = mo->array[i];

		if (mae->head != NULL) {
			MapListElement * head = mae->head;
			while (head->next != NULL)
				head = head->next;
			while (mae->chain_len > 1) {
				head = head->previous;
				free(head->next);
				chain_len--;
			}
			free(head);
		}

		free(mo->array[i]);
	}

	free(mo->array);
	free(mo);
	free(map);
};