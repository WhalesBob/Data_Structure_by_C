// 입력 받은 이차원 배열의 행의 수와 열의 수를 함수 make2DArray()에 전달하면, 함수 make2DArray()는 전달 받은 원소 갯수만큼
// 동적으로 메모리를 할당 받아 랜덤으로 100보다 작은 값으로 메모리를 초기화시킨 후, 주소값을 반환한다. 

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

int** make2DArray(rows, cols);

int main(void) {

	int** ipp;
	int rows, cols;
	printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
	scanf_s("%d %d", &rows, &cols);
	ipp = make2DArray(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("ipp[%d][%d] = %d ", i,j, ipp[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int** make2DArray(rows, cols) {
	int** x;
	MALLOC(x, rows * sizeof(*x));

	for (int i = 0; i < rows; i++) {
		MALLOC(x[i], cols * sizeof(**x));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			x[i][j] = rand() % 100;
		}
	}
	return x;
}