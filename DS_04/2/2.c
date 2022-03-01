#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#define MAX_TERMS 101

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int col;
	int row;
	int value;
}Terms;

Terms a[MAX_TERMS];
Terms b[MAX_TERMS];

void fastTranspose(Terms a[] , Terms b[]);
int** make2DArray(int rows, int cols);
void printSparce(int** x, int row, int col);

int main(void) {
	FILE* af = NULL, * bf = NULL;

	fopen_s(&af, "a.txt", "r");
	fopen_s(&bf, "b.txt", "w");

	if ((af == NULL) ||(bf == NULL)) {
		fprintf(stderr, "파일 오픈 실패");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (!feof(af)) {
		fscanf_s(af, "%d %d %d\n", &a[i].row, &a[i].col, &a[i].value);
		i++;
	}

	fastTranspose(a, b);

	for (int j = 0; j < i; j++) {
		fprintf(bf, "%d %d %d\n", b[j].row, b[j].col, b[j].value);
	}
	int** sparseA = make2DArray(a[0].row, a[0].col);
	int** sparseB = make2DArray(b[0].row, b[0].col);

	for (int i = 1; i <= a[0].value; i++) {
		sparseA[a[i].row][a[i].col] = a[i].value; // 읽어들이면서 랜덤으로 만들어진 행과 열에 값을 넣음.
	}

	for (int i = 1; i <= b[0].value; i++) {
		sparseB[b[i].row][b[i].col] = b[i].value; // 읽어들이면서 랜덤으로 만들어진 행과 열에 값을 넣음.
	}

	printf("A \n");
	printSparce(sparseA, a[0].row, a[0].col);
	printf("B \n");
	printSparce(sparseB, b[0].row, b[0].col);

	fclose(af);
	fclose(bf);

	return 0;
}
void fastTranspose(Terms a[], Terms b[]) {
	int* rowTerms, * startingPos;
	MALLOC(rowTerms, a[0].col * sizeof(int));
	MALLOC(startingPos, a[0].col * sizeof(int));

	b[0].row = a[0].col; b[0].col = a[0].row;
	b[0].value = a[0].value;

	if (a[0].value > 0) {
		for (int i = 0; i < a[0].col; i++) {
			rowTerms[i] = 0;
		}
		for (int i = 1; i <= a[0].value; i++) {
			rowTerms[a[i].col]++;
		}
		startingPos[0] = 1;
		for (int i = 1; i < a[0].col; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (int i = 1; i <= a[0].value;i++) {
			int j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
	free(startingPos);
	free(rowTerms);
}
int** make2DArray(int rows,int cols) {
	int** x;
	MALLOC(x, rows * sizeof(*x));

	for (int i = 0; i < rows; i++) {
		MALLOC(x[i], cols * sizeof(**x));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			x[i][j] = 0;
		}
	}
	return x;
}
void printSparce(int ** x,int row,int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%4d", x[i][j]);
		}
		printf("\n");
	}
}