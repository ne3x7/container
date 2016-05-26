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

void nullifier(void ** data, void * funcarg) {
	*(data) = (char *)funcarg;
}

TEST(MapTest, HashCreate) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	EXPECT_TRUE(map);
}

TEST(MapTest, HashDestroyEmpty) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	map->m->destroy(map);
}

TEST(MapTest, HashAdd) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	Iterator iter = hash_iterator_first((Hash *)map);
	EXPECT_TRUE(iter.hi.pos);
	map->m->destroy(map);
}

TEST(MapTest, HashRemove) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	void * res = map->m->remove(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	res = map->m->remove(map, &zero);
	EXPECT_FALSE(res);
	map->m->destroy(map);
}

TEST(MapTest, HashGet) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	void * res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	map->m->destroy(map);
}

TEST(MapTest, HashDestroyFull) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	map->m->destroy(map);
}

TEST(MapTest, HashForEach) {
	Map * map = (Map *) hash_create(hfunc, MAPSIZE);
	int zero = 0;
	int one = 1;
	int three = 3;
	map->m->add(map, &zero, (void *)"zero");
	map->m->add(map, &one, (void *)"one");
	map->m->add(map, &three, (void *)"three");
	map->m->foreach(map, nullifier, (void *)"changed");
	void * res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
	res = map->m->get(map, &one);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
	res = map->m->get(map, &three);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
}


TEST(MapTest, TreeCreate) {
	Map * map = (Map *) tree_create(tfunc);
	EXPECT_TRUE(map);
}

TEST(MapTest, TreeDestroyEmpty) {
	Map * map = (Map *) tree_create(tfunc);
	map->m->destroy(map);
}

TEST(MapTest, TreeAdd) {
	Map * map = (Map *) tree_create(tfunc);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	Iterator iter = tree_iterator_root((Tree *)map);
	EXPECT_TRUE(iter.ti.pos);
	map->m->destroy(map);
}

TEST(MapTest, TreeRemove) {
	Map * map = (Map *) tree_create(tfunc);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	void * res = map->m->remove(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	res = map->m->remove(map, &zero);
	EXPECT_FALSE(res);
	map->m->destroy(map);
}

TEST(MapTest, TreeGet) {
	Map * map = (Map *) tree_create(tfunc);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	void * res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "zero"), 0);
	map->m->destroy(map);
}

TEST(MapTest, TreeDestroyFull) {
	Map * map = (Map *) tree_create(tfunc);
	int zero = 0;
	map->m->add(map, &zero, (void *)"zero");
	map->m->destroy(map);
}

TEST(MapTest, TreeForEach) {
	Map * map = (Map *) tree_create(tfunc);
	int zero = 0;
	int one = 1;
	int two = 2;
	map->m->add(map, &one, (void *)"one");
	map->m->add(map, &zero, (void *)"zero");
	map->m->add(map, &two, (void *)"two");
	map->m->foreach(map, nullifier, (void *)"changed");
	void * res = map->m->get(map, &zero);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
	res = map->m->get(map, &one);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
	res = map->m->get(map, &two);
	EXPECT_EQ(strcmp((char *) res, "changed"), 0);
}