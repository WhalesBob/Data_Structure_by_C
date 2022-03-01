#include <stdio.h>
#include <math.h>

void sort(int list[], int n);
void swap(int* x, int* y);
int binarySearch(int* point, int searchNum);

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

	result = binarySearch(point, toSearch, n);
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
int binarySearch(int* point, int searchNum, int size) {
	int left = 0;
	int right = size - 1;
	int middle;

	while (left <= right) {
		middle = (left + right) / 2;
		if (searchNum < point[middle]) {
			right = middle - 1;
		}
		else if (searchNum == point[middle]) {
			return middle;
		}
		else {
			left = middle + 1;
		}
	}
}
