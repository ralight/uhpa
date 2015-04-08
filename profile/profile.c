/*
 * This program loads in a set of sizes of memory to be allocated (stored as
 * 16-bit ints) from alloc.dat, then sets about allocating and using the memory
 * elements using UHPA.
 *
 * When compiling, define MAX_ARRAY_SIZE to the UHPA array size you wish to
 * test. Use different sizes and run the resulting program under e.g. callgrind
 * to see the performance cost.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "uhpa.h"

typedef union {
	char *ptr;
	char array[MAX_ARRAY_SIZE];
} uhpa_c_t;

typedef struct {
	short len;
	uhpa_c_t uhpa;
} data_t;

int main(int argc, char *argv[])
{
	int i;
	long alloc_count;
	data_t *data;
	FILE *fptr;
	uint16_t *alloc;
	int infill[1024];

	for(i=0; i<1024; i++){
		infill[i] = i%255;
	}

	fptr = fopen("alloc.dat", "rb");
	if(!fptr){
		fprintf(stderr, "Unable to open alloc.dat.\n");
		return 1;
	}

	fseek(fptr, 0L, SEEK_END);
	alloc_count = ftell(fptr)/2;
	fseek(fptr, 0L, SEEK_SET);

	alloc = malloc(alloc_count*2);
	if(!alloc){
		fclose(fptr);
		fprintf(stderr, "Out of memory.\n");
		return 1;
	}
	fread(alloc, 2, alloc_count, fptr);
	fclose(fptr);

	data = calloc(alloc_count, sizeof(data_t));
	if(!data){
		free(alloc);
		fprintf(stderr, "Out of memory.\n");
		return 1;
	}

	for(i=0; i<alloc_count; i++){
		data[i].len = alloc[i];
		if(UHPA_ALLOC(data[i].uhpa, alloc[i]) == 0){
			fprintf(stderr, "Out of memory.\n");
			return 1;
		}
		memcpy(UHPA_ACCESS(data[i].uhpa, alloc[i]), infill, alloc[i]);
	}

	for(i=0; i<alloc_count; i++){
		UHPA_FREE(data[i].uhpa, alloc[i]);
	}
	free(data);
	free(alloc);

	return 0;
}

