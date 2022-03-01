//크기가 20*20인 이차원 배열로 희소 행렬을 다음과 같이 만들어라. 0이 아닌 배열 원소의
//수를 입력 받아, rand()함수를 이용하여 위치와 값을 설정하도록 하시오. (원소의 개수는 입력
//받은 수만큼 되어 야함. 매번 수행시마다 서로 다른 희소행렬이 만들어져야함), 이 행렬을 이
//용하여, 배열의 공간을 절약하기 위한 형태의 희소행렬을 만들고 출력하시오. 

// Sparse Matrix

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
	printf("원소의 개수를 쓰시오 : ");

	scanf_s("%d", &n); // 원소 개수 입력 완료

	a[0].row = 20;
	a[0].col = 20;
	a[0].value =  n; // sparse matrix에 초기 값을 줌.

	for (int i = 1; i < n;) {
		a[i].row = rand() % 20;
		a[i].col = rand() % 20;
		a[i].value = (rand() % 99) + 1 ; // 입력을 줌. 이렇게 하면 value에 필연적으로 1 이상의 값이 찍힘.
		if (!((a[i].row == a[i - 1].row) && (a[i].col == a[i - 1].col))) { // 행과 열이 완전히 같지 않으면,
			i++; //i를 증가시킴. 만약에 이걸 통과를 못하면, 다시 똑같이 돌겠지.
		}
	} // 이까지 하면 다 완성이 됨. 애초에 a[0]하고는 둘다 겹칠수가 없음. 입력 완료

	int sparce[20][20] = { 0 };
	
	// 이제 그러면 안에 집어 넣어 보자. 
	for (int i = 1; i < n; i++) {
		sparce[a[i].row][a[i].col] = a[i].value; // 읽어들이면서 랜덤으로 만들어진 행과 열에 값을 넣음.
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