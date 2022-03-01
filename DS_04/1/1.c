#define MAX_TERMS 101

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int col;
	int row;
	int value;
}Terms;

Terms a[MAX_TERMS];

int main(void) {
	
	int n;
	printf("������ ������ ���ÿ� : ");

	scanf_s("%d", &n); // ���� ���� �Է� �Ϸ�

	a[0].row = 20;
	a[0].col = 20;
	a[0].value =  n; // sparse matrix�� �ʱ� ���� ��.

	for (int i = 1; i < n;) {
		a[i].row = rand() % 20;
		a[i].col = rand() % 20;
		a[i].value = (rand() % 99) + 1 ; // �Է��� ��. �̷��� �ϸ� value�� �ʿ������� 1 �̻��� ���� ����.
		if (!((a[i].row == a[i - 1].row) && (a[i].col == a[i - 1].col))) { // ��� ���� ������ ���� ������,
			i++; //i�� ������Ŵ. ���࿡ �̰� ����� ���ϸ�, �ٽ� �Ȱ��� ������.
		}
	} // �̱��� �ϸ� �� �ϼ��� ��. ���ʿ� a[0]�ϰ�� �Ѵ� ��ĥ���� ����. �Է� �Ϸ�

	int sparce[20][20] = { 0 };
	
	// ���� �׷��� �ȿ� ���� �־� ����. 
	for (int i = 1; i < n; i++) {
		sparce[a[i].row][a[i].col] = a[i].value; // �о���̸鼭 �������� ������� ��� ���� ���� ����.
	}

	printf("Random generated Matrix(20,20) \n");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			printf("%4d", sparce[i][j]);
		}
		printf("\n");
	}
	printf("sparce matrix \n");
	for (int i = 0; i < n; i++) {
		printf("%d,	%d	%d \n", a[i].row, a[i].col, a[i].value);
	}
	
	return 0;
}