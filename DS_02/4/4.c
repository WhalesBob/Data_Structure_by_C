// 3번 소스에 대해 데이터 생성부분을 일부 수정하여 다음 3가지 경우에 대해 성능측정을 하여 비교하라.
// 그리고 selection sort 알고리즘의 경우 worst-case, best-case, average-case data의 구분이 있는지 기술하라.

// 1. 입력데이터가 내림차순 정렬이 이미 되어 있는 경우
// 2. 입력데이터가 오름차순 정렬이 이미 되어 있는 경우
// 3. 입력데이터를 난수생성으로 만들어 사용하는 경우

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_SIZE 1001

void sort(int a[], int n);
void swap(int* a, int* b);

int main(void) {

	int step = 10;
	int a[MAX_SIZE];
	double duration;

	FILE* fp = NULL;
	fopen_s(&fp, "out4.txt", "w");

	fprintf(fp, "	n	repetitions	time\n");
	printf("	n	repetitions	time\n");

	for (int n = 0; n <= 1000; n += step) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;

			for (int i = 0; i < n; i++) {
				a[i] = rand() % n;
			}
			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		duration /= repetitions;
		printf("%6d %9d %f \n", n, repetitions, duration);
		fprintf(fp, "%6d %9d %f \n", n, repetitions, duration);
		if (n == 100) {
			step = 100;
		}
	}
	return 0;
}
void sort(int a[], int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
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