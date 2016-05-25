# Раскроет тильду как /home/nickstulov
GTEST_DIR = $(shell echo ~/Desktop/prog3/googletest-master/googletest)

USER_DIR = ..

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

TESTS = map_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h  $(GTEST_DIR)/include/gtest/internal/*.h

all: $(TESTS)

clean:
	rm -f $(TESTS) gtest.a gtest_main.a *.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

hash.o: $(USER_DIR)/hash.c $(USER_DIR)/hash.h $(GTEST_HEADERS)
	$(CC) -c $(CXXFLAGS) $(USER_DIR)/hash.c -o hash.o

tree.o: $(USER_DIR)/tree.c $(USER_DIR)/tree.h $(GTEST_HEADERS)
	$(CC) -c $(CXXFLAGS) $(USER_DIR)/tree.c -o tree.o

map_unittest.o: map_unittest.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c map_unittest.cc -o map_unittest.o

map_unittest: hash.o tree.o map_unittest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@