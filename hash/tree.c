#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "map.h"

#define TREEOBJ(tree) (TreeObject *) ((char *)tree + sizeof(Tree))

MapMethods TreeMethods = {
	tree_add,
	tree_remove,
	tree_foreach,
	tree_get,
	tree_destroy
};

// <<---------------------------------------------- Types & Structs ----------------------------------------------->>

typedef struct TreeObject {
	int (* hash)(void * data);
	struct Node * root;
} TreeObject;

typedef struct Node {
	int key;
	void * value;
	struct Node * parent;
	struct Node * lchild;
	struct Node * rchild;
} Node;

// <<-------------------------------------------- TreeIterator methods -------------------------------------------->>

Iterator tree_iterator_root(Tree * t) {
	TreeObject * to = TREEOBJ(t);
	TreeIterator ti;
	Iterator iter;

	ti.pos = to->root;
	iter.ti = ti;

	return iter;
};

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

	if (root == NULL)
		to->root = toadd;
	else
		while(1) {
			if (index < root->key) {
				if (root->lchild == NULL) {
					root->lchild = toadd;
					return;
				}
				else
					root = root->lchild;
			}
			else if (index > root->key) {
				if (root->rchild == NULL) {
					root->rchild = toadd;
					return;
				}
				else
					root = root->rchild;
			}
			else {
				root->value = value;
				free(toadd);
				return;
			}
		}
};
void * tree_remove(Tree * t, void * key) {
	TreeObject * to = TREEOBJ(t);
	Node * root = to->root;
	void * vtr = NULL;
	int index = to->hash(key);

	while (root != NULL) {
		if (index < root->key) {
			root = root->lchild;
			continue;
		}
		else if (index > root->key) {
			root = root->rchild;
			continue;
		}
		else {
			vtr = root->value;

			if ((root->lchild == NULL) && (root->rchild == NULL)) {
				if (root = to->root) {
					free(to->root);
					to->root = NULL;
					return vtr;
				}

				if (root->parent->lchild == root)
					root->parent->lchild = NULL;
				else
					root->parent->rchild = NULL;

				free(root);
				return vtr;
			}

			if ((root->lchild != NULL) && (root->rchild != NULL)) {
				Node * replace = root->rchild;

				while (replace->lchild != NULL)
					replace = replace->lchild;

				int mem = replace->key;
				root->value = tree_remove(t, &mem);
				root->key = mem;

				return vtr;
			}

			if (root->lchild != NULL) {
				root->lchild->parent = root->parent;

				if (root->parent != NULL) {
					if (root->parent->lchild == root)
						root->parent->lchild = root->lchild;
					else
						root->parent->rchild = root->lchild;
				}
				else
					to->root = root->lchild;
			}
			else {
				root->rchild->parent = root->parent;

				if (root->parent != NULL) {
					if (root->parent->lchild == root)
						root->parent->lchild = root->rchild;
					else
						root->parent->rchild = root->rchild;
				}
				else
					to->root = root->rchild;

				free(root);
				return vtr;
			}
		}
	}

	return vtr;
};
void tree_apply(Node * node, void (* func)(void ** data, void * funcarg), void * arg) {
	func(&(node->value), arg);

	if (node->lchild != NULL)
		tree_apply(node->lchild, func, arg);
	if (node->rchild != NULL)
		tree_apply(node->rchild, func, arg);
};
void tree_foreach(Tree * t, void (* func)(void ** data, void * funcarg), void * arg) {
	TreeObject * to = TREEOBJ(t);

	if (to->root != NULL)
		tree_apply(to->root, func, arg);
};
void * tree_get(Tree * t, void * key) {
	TreeObject * to = TREEOBJ(t);
	Node * root = to->root;
	int index = to->hash(key);

	if (root == NULL)
		return NULL;
	else
		while(1) {
			if (index < root->key) {
	            if (root->lchild == NULL)
	                return NULL;

            	root = root->lchild;
	        }
	        else if (index > root->key) {
	            if (root->rchild == NULL)
	                return NULL;

	            root = root->rchild;
	        }
	        else
	            return root->value;
		}
};
void tree_destroyer(Node * node) {
	if (node->lchild != NULL)
		tree_destroyer(node->lchild);
	node->lchild = NULL;

	if (node->rchild != NULL)
		tree_destroyer(node->rchild);
	node->rchild = NULL;

	free(node);
};
void tree_destroy(Tree * t) {
	TreeObject * to = TREEOBJ(t);
	if (to->root != NULL)
		tree_destroyer(to->root);
	free(t);
};
/*
void tree_levels(Node * n, int depth) {
	int i;
    for (i = 0; i < depth; i++) {
        printf("-");
    }
    if (n == NULL) {
        return;
    }
    printf("(%d, %s)\n", n->key, n->value);
    if (n->lchild != NULL) tree_levels(n->lchild, depth+1);
    if (n->rchild != NULL) tree_levels(n->rchild, depth+1);
};
void tree_trace(Tree * t) {
	TreeObject * to = TREEOBJ(t);
	if (to->root != NULL)
		tree_levels(to->root, 0);
};
*/