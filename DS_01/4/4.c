// 100�� �̸��� ������ ������ �Է¹޾�, ���� �Է� ���� ���� ��ŭ ������ �����Ѵ�. ������ ������ ���ؼ�
// ���� ����(Selection Sort)�� �����ϴ� ���α׷��� �ۼ��Ͻÿ�. ���ĵ� �������� ������ ���Ҹ� ã�� ���� �������
// ����� ����ϴ� binary search ���α׷��� �ۼ��Ͻÿ�. ����Լ� ȣ��ø��� ã�� ������ left�� right �ε��� ���� ����Ͻÿ�

// 1. ����ڷκ��� �������� ����(n)�� �Է¹޴´�\
// 2. ���� ������ n�� �߻����� 1���� �迭�� �����Ѵ�.
// 3. 1���� �迭�� ���� ��������(selection sort)�� �����Ѵ�. �������� ����Ѵ�. 
// 4. �˻��� ���� ������ ������ �Է¹޴´�
// 5. �Է¹��� ������ �迭�� �ִ��� �ݺ����� ������� ����Ž��(binary search)�� �����ϴ� ���α׷��� �ۼ��Ͻÿ�.

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