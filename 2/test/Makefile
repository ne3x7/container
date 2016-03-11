# Раскроет тильду как /home/nickstulov
GTEST_DIR = $(shell echo ~/Desktop/prog3/googletest-master/googletest)

USER_DIR = ..

CPPFLAGS += -isystem $(GTEST_DIR)/include

CCFLAGS += $(USER_DIR)/list.h

CXXFLAGS += -g -Wall -Wextra -pthread

TESTS = list_unittest

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

list.o: $(USER_DIR)/list.c $(USER_DIR)/list.h $(GTEST_HEADERS)
	$(CC) -c $(CXXFLAGS) $(USER_DIR)/list.c -o list.o

list_unittest.o: list_unittest.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c list_unittest.cc -o list_unittest.o

list_unittest: list.o list_unittest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@