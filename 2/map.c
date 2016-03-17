#include <stdio.h>
#include <stdlib.h>

#include "map.h"

#define MAPOBJ(map) (MapObject *) ((char *)map + sizeof(Map))

HashMethods MapMethods = {
	map_create,
	map_add,
	map_remove,
	foreach,
	map_size,
	map_at,
	map_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct MapObject { // у каждого экземпляра map свой массив
	int (* hash)(void * data); // хэш-функция
	MapArrayElement ** array; // массив указателей
	int size;
} MapObject;

typedef struct MapArrayElement { // у каждого элемента массива есть хэш и цепочка
	int hash; // нужен ли hash? посмотреть хэш-функции, идеально было бы нумеровать натуральным рядом
	int chain_len;
	MapListElement * head; // можно хранить только голову и работать как со списком
} MapArrayElement;

typedef struct MapListElement { // элементы цепочки имеют ключ и значение
	MapListElement * previous;
	void * key;
	void * value;
	MapListElement * next;
} MapElement;

// <<-------------------------------------------- MapIterator methods --------------------------------------------->>

Iterator map_iterator_first(Map * m);
Iterator map_iterator_last(Map * m);
Iterator * map_iterator_forward(Map * m, Iterator iter);
Iterator * map_iterator_backward(Map * m, Iterator iter);

// <<------------------------------------------------ Map methods ------------------------------------------------->>

Map * map_create(int (* hash)(void * key, void * value), int size) { // пока так
	Map * map = malloc(sizeof(Map) + sizeof(MapObject));
	map->m = MapMethods;
	MapObject * mo = MAPOBJ(map);
	mo->hash = hash;
	mo->size = size;
	mo->array = malloc(size * sizeof(MapArrayElement));
	return map;
};
void map_add(Map * map, void * key, void * value) { // возможно, я что-то делаю не так
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
void * map_remove(Map * map, void * key) {
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
// void foreach(Map * map, void (* func)(void * data, void * funcarg), void * arg);
int map_size(Map * map) {
	// пройтись по всем
};
void * map_at(Map * map, void * key) {
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
void map_destroy(Map * map) {
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