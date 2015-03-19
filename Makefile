CC=gcc
CFLAGS=-Wall -ggdb

all : uhpa_example_10 uhpa_example_15

uhpa_example_10 : uhpa_example.c
	$(CC) -o $@ $^ $(CFLAGS) -DUHPA_UNION_SIZE=10

uhpa_example_15 : uhpa_example.c
	$(CC) -o $@ $^ $(CFLAGS) -DUHPA_UNION_SIZE=15

memtest_10 : uhpa_example_10
	valgrind -v --show-reachable=yes --leak-check=full ./$^

memtest_15 : uhpa_example_15
	valgrind -v --show-reachable=yes --leak-check=full ./$^

test : all
	./uhpa_example_10
	./uhpa_example_15

memtest : memtest_10 memtest_15

clean :
	-rm -f uhpa_example_10 uhpa_example_15 *.o

