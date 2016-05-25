#include <limits.h>
#include "../hash.h"
#include "../tree.h"
#include "gtest/gtest.h"

int MAPSIZE = 10;

int hfunc(void * key) {
	return *((int *) key) % MAPSIZE;
}

int tfunc(void * key) {
	return *((int *) key);
}

TEST(MapTest, HashCreate) {
	Hash * hash = hash_create(hfunc, MAPSIZE);
	EXPECT_TRUE(hash);
}