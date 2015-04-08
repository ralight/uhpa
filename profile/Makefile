CC=gcc
CFLAGS=-Wall -ggdb -I..

profile : 
	for a in $$(seq 1 100); do \
		$(CC) ${CFLAGS} -o profile_$$a -DMAX_ARRAY_SIZE=$$a profile.c ; \
	done

callgrind : 
	for a in $$(seq 1 100); do \
		valgrind --tool=callgrind --callgrind-out-file=callgrind.out.$$a.%p ./profile_$$a ; \
	done

clean :
	-rm -f uhpa_example_10 uhpa_example_15 *.o

