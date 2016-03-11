#include <limits.h>
#include "../list.h"
#include "gtest/gtest.h"

TEST(ListTest, Create) {
	List * l = list_create();
	EXPECT_TRUE(l);
}

TEST(ListTest, InsertFirst) {
	List * l = list_create();
	l->m->insert_first(l, (void *)"one");
	Iterator iter = l->m->first(l);
	EXPECT_TRUE(iter.li.pos);
}

TEST(ListTest, InsertLast) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	Iterator iter = l->m->first(l);
	EXPECT_TRUE(iter.li.pos);
}

TEST(ListTest, First) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	Iterator iter = l->m->first(l);
	EXPECT_TRUE(iter.li.pos);
	void * data = l->m->get(iter);
	EXPECT_TRUE(data);
}

TEST(ListTest, Last) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	Iterator iter = l->m->last(l);
	EXPECT_TRUE(iter.li.pos);
	void * data = l->m->get(iter);
	EXPECT_TRUE(data);
}

TEST(ListTest, Multiple) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	l->m->insert_last(l, (void *)"two");
	Iterator first = l->m->first(l);
	Iterator last = l->m->last(l);
	EXPECT_TRUE(iter.li.pos);
	void * data = l->m->get(iter);
	EXPECT_TRUE(data);
}