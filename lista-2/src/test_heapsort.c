#include <stdio.h>
#include <stdlib.h>
#include <heapsort.h>
#include <time.h>

/* 
	Função para cálculo de diferença de tempo entre duas 'struct timespec'.
	Retorna o tempo em segundos.
*/
double diff_seconds(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}

	return (double) (temp.tv_sec + (double) temp.tv_nsec/1000000000L);
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage:\n\t%s <VECTORS_SIZE>\n", argv[0]);
		return -1;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		printf("ERROR: Size must be bigger than 0\n");
		return -1;
	}

	struct timespec start, stop;
	double delta_local, delta_separated;
	
	Vector *v = vector_new(size);
	Vector *h = vector_new(size);
	Vector *v2 = vector_new(size);
	
	vector_fill(v);
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
	vector_heapsort(v);
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
	delta_local = diff_seconds(start, stop);
	
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
	heap_fill(h);
	heap_move_roots_to_vector(h, v2);
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
	delta_separated = diff_seconds(start, stop);

	printf("%d;%lf;%lf\n", size, delta_local, delta_separated);

	return 0;
}