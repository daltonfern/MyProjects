
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static inline double frand(int maxVal) {
	return ((double) rand()) / ((double) RAND_MAX) * ((double) maxVal) ;
}


static inline void printMat(double* A, int N) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			fprintf(stderr, " %f", A[i*N + j]);
		}
		fprintf(stderr, "\n");
	}
}


void Normalize1(double* A, int N) {
	double t, min = (double) RAND_MAX, max = 0.0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			t = A[i*N + j];
			if (t < min) min = t;
			if (t > max) max = t;
		}
	}

	double frac = 1 / (max - min);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			A[i*N + j] = (A[i*N + j] - min) * frac;
		}
	}
}


void Normalize2(double* A, int N) {
	double t, min = (double) RAND_MAX, max = 0.0;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			t = A[i*N + j];
			if (t < min) min = t;
			if (t > max) max = t;
		}
	}

	double frac = max - min;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			A[i*N + j] = (A[i*N + j] - min) / frac;
		}
	}
}


int main(int argc, char** argv) {

	int whichAlg = 1;
	int N = 1 << 4;
	int max = 20;
	
	if (argc > 1) {
		whichAlg = atoi(argv[1]);
	}
	if (argc > 2) {
		N = atoi(argv[2]);
	}
	if (argc > 3) {
		max = atoi(argv[3]);
	}

	srand(time(NULL));

	double* A = (double*) malloc(sizeof(double)*N*N);
	if (A == NULL) {
		fprintf(stderr, "Error: could not allocate the matrix!\n");
		return 1;
	}	

	for (int i = 0; i < N*N; ++i) { 
		A[i] = frand(max);
	}

//	printMat(A, N);

	if (whichAlg <= 1) {
//		fprintf(stderr, "Normalize1\n");
		Normalize1(A, N);
	} else {
//		fprintf(stderr, "Normalize2\n");
		Normalize2(A, N);
	}

//	printMat(A, N);

	free(A);
	return 0;
}

