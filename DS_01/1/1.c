// 형식 매개변수가 다른 세 가지 버전의 함수를 각각 정의하고 실행되도록 작성하라. 

// 프로그램 설명
// int sunAry2D_f1(int ary[][3], int ROW, int COL); // 배열파라미터 // 권장
// int sumAry2D_f2(int (*ary)[3], int ROW) // 배열포인터
// int sumAry2D_f3[3][3];

#include <stdio.h>

int sumAry2D_f1(int ary[][3],int ROW, int COL);
int sumAry2D_f2(int(*ary)[3], int ROW);
int sumAry2D_f3(int ary[3][3]);

int main(void) {

	int ROW = 3;
	int COL = 3;

	int ary2D[][3] = { {1,2,3},{4,5,6},{7,8,9} };

	printf("sumAry2D_f1() %d \n", sumAry2D_f1(ary2D, ROW, COL));
	printf("sumAry2D_f2() %d \n", sumAry2D_f2(ary2D, ROW));
	printf("sumAry2D_f3() %d \n", sumAry2D_f3(ary2D));

	return 0;
}
int sumAry2D_f1(int ary[][3], int ROW, int COL) {
	int total = 0;

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			total += ary[i][j];
		}
	}
	return total;
}
int sumAry2D_f2(int (*ary)[3], int ROW) {
	int total = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < ROW; j++) {
			total += ary[i][j];
		}
	}
	return total;
}
int sumAry2D_f3(int ary[3][3]) {
	int total = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			total += ary[i][j];
		}
	}
	return total;
}

