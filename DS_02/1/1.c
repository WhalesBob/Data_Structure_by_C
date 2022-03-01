#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int* func1(void);
void func2(int* p);
void func3(int** pp);
char* func4(int n);

int main(void) {

	int* pNum;
	char* pChar;

	pNum = func1();
	printf("%d \n", *pNum);

	func2(pNum);
	printf("%d \n", *pNum);

	func3(&pNum);
	printf("%d \n",*pNum);

	pChar = func4(1000);
	int pCharSize = _msize(pChar);

	printf("입력할 문자열 : ");
	scanf_s("%s", pChar, pCharSize);
	printf("pChar Contents = %s \n", pChar);

	free(pNum);
	free(pChar);
	
	return 0;
}
int* func1() {
	int* a = (int*)malloc(sizeof(int));
	*a = 10;
	return a;
}
void func2(int* p) {
	*p = 100;
}
void func3(int** pp) {
	**pp = 200;
}
char* func4(int n) {
	char* str = (char*)calloc(n,sizeof(char));
	return str;
}