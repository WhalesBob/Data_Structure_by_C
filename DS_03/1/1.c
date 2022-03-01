#include <stdio.h>
#include <stdlib.h>

int* make1dArray(num);

int main(void) {

	int* ipp;
	int num;

	printf("일차원 배열의 수를 입력하세요 : ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);
	for (int i = 0; i < num; i++) {
		printf("ipp[%2d] = %2d ", i, ipp[i]);
		if ((i % 5) == 4) {
			printf("\n");
		}
	}
	return 0;
}
int* make1dArray(num) {
	int* p = calloc(num, sizeof(int));
	if (p == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num; i++) {
		p[i] = rand() % 100;
	}

	return p;
}