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
	EXPECT_TRUE(first.li.pos);
	EXPECT_TRUE(last.li.pos);
	void * data1 = l->m->get(first);
	void * data2 = l->m->get(last);
	EXPECT_TRUE(data1);
	EXPECT_TRUE(data2);
}

TEST(ListTest, Next) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	l->m->insert_last(l, (void *)"two");
	Iterator first = l->m->first(l);
	Iterator last = list_iterator_next(first);
	EXPECT_TRUE(first.li.pos);
	EXPECT_TRUE(last.li.pos);
	void * data1 = l->m->get(first);
	void * data2 = l->m->get(last);
	EXPECT_TRUE(data1);
	EXPECT_TRUE(data2);
}

TEST(ListTest, Prev) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	l->m->insert_last(l, (void *)"two");
	Iterator last = l->m->last(l);
	Iterator first = list_iterator_prev(last);
	EXPECT_TRUE(first.li.pos);
	EXPECT_TRUE(last.li.pos);
	void * data1 = l->m->get(first);
	void * data2 = l->m->get(last);
	EXPECT_TRUE(data1);
	EXPECT_TRUE(data2);
}

TEST(ListTest, DeleteLast) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	l->m->insert_last(l, (void *)"two");
	Iterator last = l->m->last(l);
	Iterator first = list_iterator_prev(last);
	EXPECT_TRUE(first.li.pos);
	EXPECT_TRUE(last.li.pos);
	void * data = l->m->delete_last(l);
	EXPECT_TRUE(data);
}

TEST(ListTest, Destroy) {
	List * l = list_create();
	l->m->insert_last(l, (void *)"one");
	l->m->insert_last(l, (void *)"two");

	l->m->destroy(l);
}