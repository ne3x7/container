#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "map.h"

#define TREEOBJ(tree) (TreeObject *) ((char *)tree + sizeof(Tree))

MapMethods TreeMethods = {
	tree_add,
	tree_remove,
	tree_get,
	tree_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct TreeObject {
	int (* hash)(void * data);
	struct Node * root;
} TreeObject;

typedef struct Node {
	void * key;
	void * value;
	struct Node * parent;
	struct Node * lchild;
	struct Node * rchild;
} Node;

// <<-------------------------------------------- TreeIterator methods -------------------------------------------->>

// <<------------------------------------------------ Tree methods ------------------------------------------------>>

Tree * tree_create(int (* hash)(void * key)) {
	Tree * t = malloc(sizeof(Tree) + sizeof(TreeObject));
	t->m = &TreeMethods;
	TreeObject * to = TREEOBJ(t);
	to->hash = hash;
	to->root = NULL;
	return t;
};
void tree_add(Tree * t, void * key, void * value) {
	TreeObject * to = TREEOBJ(t);
	Node * root = to->root;
	int index = to->hash(key);

	Node * toadd = malloc(sizeof(Node));
	toadd->key = index; // хранить уже хэшированные ключи
	toadd->value = value;
	toadd->parent = NULL;
	toadd->lchild = NULL;
	toadd->rchild = NULL;

	if (root = NULL)
		to->root = toadd;
	else {
		if (index < root->key)
	}
};
void * tree_remove(Tree * t, void * key);
// void tree_foreach(Tree * t, void (* func)(void * data, void * funcarg), void * arg);
void * tree_get(Tree * t, void * key);
void tree_destroy(Tree * t);