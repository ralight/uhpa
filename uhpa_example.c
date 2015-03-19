#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "uhpa.h"

#define STR_ARRAY "hello world"
#define STR_HEAP "how now brown cow"

typedef union {
	char *ptr;
	char array[UHPA_UNION_SIZE];
} uhpa_c_t;

struct s {
	short len;
	uhpa_c_t s;
};

int main(int argc, char *argv[])
{
	struct s st_array, st_heap;

	printf("=======================\n");
	printf("Array size is %d bytes.\n", UHPA_UNION_SIZE);

	st_array.len = strlen(STR_ARRAY);
	printf("\nAttempting to store data '%s' that is %d bytes long.\n", STR_ARRAY, st_array.len);
	printf("Alloc type: %d (1 is heap, 0 is heap fail, -1 is array)\n", UHPA_ALLOC_STR(st_array.s, st_array.len));
	sprintf(UHPA_ACCESS_STR(st_array.s, st_array.len), STR_ARRAY);
	printf("Read from struct: %s\n", UHPA_ACCESS_STR(st_array.s, st_array.len));
	UHPA_FREE_STR(st_array.s, st_array.len);

	st_heap.len = strlen(STR_HEAP);
	printf("\nAttempting to store data '%s' that is %d bytes long.\n", STR_HEAP, st_heap.len);
	printf("Alloc type: %d (1 is heap, 0 is heap fail, -1 is array)\n", UHPA_ALLOC_STR(st_heap.s, st_heap.len));
	sprintf(UHPA_ACCESS_STR(st_heap.s, st_heap.len), STR_HEAP);
	printf("Read from struct: %s\n", UHPA_ACCESS_STR(st_heap.s, st_heap.len));
	UHPA_FREE_STR(st_heap.s, st_heap.len);

	return 0;
}

