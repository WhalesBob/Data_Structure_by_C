#define MAX_SIZE 1001

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void sort(int a[], int n);
void swap(int* a, int* b);

int main(void) {
	int step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;
	FILE* f;
	fopen_s(&f, "out.txt", "w");
	if (f == NULL) {
		printf("파일 오픈 실패 \n");
		exit(EXIT_FAILURE);
	}

	printf("	n	time\n");
	fprintf(f, "	n	time\n");
	for (int n = 0; n <= 1000; n += step) {
		for (int i = 0; i < n; i++) {
			a[i] = n - i;
		}
		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		fprintf(stdout, "%6d	%f \n", n, duration);
		fprintf(f, "%6d	%f \n", n, duration);
		if (n == 100) {
			step = 100;
		}
	}
	fclose(f);

	return 0;
}
void sort(int a[], int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		swap(&a[i], &a[min]);
	}
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}