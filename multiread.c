#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int num_threads = 1;
char read_file[100];
struct timespec start, finish;
clock_t ticks_start, ticks_finish;

#define NUM_CHARS 100000000

void *ReadFile(void *id) {
	FILE *fi = fopen(read_file, "rb");
	fseek(fi, NUM_CHARS / (long long)num_threads * (long long)id, SEEK_SET);
	int ch;
	int i;
	for (i = 0; i < NUM_CHARS / (long long)num_threads; ++i) {
		ch = fgetc(fi);
	}
	fclose(fi);
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	long i;
	if (argc == 3) {
		// read in args
		num_threads = atoi(argv[1]);
		strcpy(read_file, argv[2]);

		// read file, or create file
		if (access(read_file, F_OK) != -1) {
			// printf("Using existing file\n");
		}
		else {
			// printf("Writing file %s\n", read_file);
			FILE *fi = fopen(read_file, "w");
			if (fi !=NULL)
				for (i = 0; i < NUM_CHARS; ++i)
					fputc ('x', fi);
			fclose(fi);
		}

		// launch threads to read file
		// printf("Launching threads\n", read_file);
		ticks_start = clock();
		clock_gettime(CLOCK_MONOTONIC, &start);
		pthread_t *pt = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
		for (i = 0; i < num_threads; ++i)
			pthread_create(&pt[i], NULL, ReadFile, (void *)i);
		for (i = 0; i < num_threads; ++i)
			pthread_join(pt[i], NULL);

		// print timing
		clock_gettime(CLOCK_MONOTONIC, &finish);
		double elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		ticks_finish = clock();
		printf("%.5f\t%.5f\n", elapsed, (double)(ticks_finish - ticks_start) / CLOCKS_PER_SEC);
	}
	else {
		printf("Needs two args: num_threads read_file\n");
	}
	return 0;
}
