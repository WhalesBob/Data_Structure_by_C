// 아래 프로그램을 이용하여 선택정렬(Selection Sort)에 대한 성능측정을 하라. 그리고 프로그램의 실행결과를 이용하여
// 그래프를 작성하라. 또한, 문제 2의 결과와 같이 하나의 그래프로 작성해 비교해 보라. (Code Ver.)

#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001

void sort(int a[], int n);
void swap(int* a, int* b);

int main(void) {

	int step = 10;
	int a[MAX_SIZE];
	double duration;

	FILE* fp = NULL;
	fopen_s(&fp, "out2.txt", "w");

	fprintf(fp, "	n	repetitions	time\n");
	printf("	n	repetitions	time\n");

	for (int n = 0; n <= 1000; n += step) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;

			for (int i = 0; i < n; i++) {
				a[i] = n - i;
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