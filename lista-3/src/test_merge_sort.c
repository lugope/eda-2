#include "merge_sort.h"

int main(int argc, char *argv[]){

	if(argc != 2){
		fprintf(stderr, "Correct usage: %s <VECTOR_LENGTH>\n", argv[0]);
		exit(-1);
	}

	int *vec, length;

	length = atoi(argv[1]);
	vec = create_vector(length);

	printf("Before - ");
	print_vector(vec, length);

	merge_sort(0, length-1, vec);

	printf("\nAfter - ");
	print_vector(vec, length);	

	return 0;
}
