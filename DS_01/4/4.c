// 100개 미만의 원소의 개수를 입력받아, 받은 입력 원소 개수 만큼 난수를 생성한다. 생성된 난수에 대해서
// 선택 정렬(Selection Sort)를 수행하는 프로그램을 작성하시오. 정렬된 난수에서 임의의 원소를 찾기 위해 재귀적인
// 방법을 사용하는 binary search 프로그램을 작성하시오. 재귀함수 호출시마다 찾는 범위를 left와 right 인덱스 값을 출력하시오

// 1. 사용자로부터 난수생성 개수(n)을 입력받는다\
// 2. 정수 난수를 n개 발생시켜 1차원 배열에 저장한다.
// 3. 1차원 배열에 대해 선택정렬(selection sort)를 수행한다. 수행결과를 출력한다. 
// 4. 검색을 위해 임의의 정수를 입력받는다
// 5. 입력받은 정수가 배열에 있는지 반복적인 방법으로 이진탐색(binary search)를 수행하는 프로그램을 작성하시오.

#include <stdio.h>
#include <math.h>

void sort(int* point, int n);
void swap(int* x, int* y);
int compare(int x, int y);
int binarySearch(int* point, int searchNum,int left, int right);

int main(void) {
	int n;
	int* point = NULL;
	int toSearch;
	int result;

	printf("Enter the number of numbers to generate : ");
	scanf_s("%d", &n);

	point = calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		point[i] = rand() % 1000;
		printf("%d ", point[i]);
	}
	sort(point, n);
	printf("\n\nSorted array : \n");
	for (int i = 0; i < n; i++) {
		printf("%d ", point[i]);
	}
	printf("\n\n");
	printf("Enter the number to search : ");
	scanf_s("%d", &toSearch);

	result = binarySearch(point, toSearch, 0, n-1);
	printf("The search number is present in list[%d] \n", result);

	return 0;
}
void sort(int* point, int n) {
	int min, temp;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (point[j] < point[min]) {
				min = j;
			}
		}
		swap(&point[i], &point[min]);
	}
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}
int compare(int x, int y) {
	if (x < y) {
		return -1;
	}
	else if (x == y) {
		return 0;
	}
	else {
		return 1;
	}
	
}

int binarySearch(int* point, int searchNum, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		printf("call binsearch_recur, left : %d, right : %d \n", left, right);
		switch (compare(point[middle], searchNum)) {
		case -1:
			return binarySearch(point, searchNum, middle + 1, right);
		case 0:
			return middle;
		case 1:
			return binarySearch(point, searchNum, left, middle - 1);
		};
	}
	return -1;
}