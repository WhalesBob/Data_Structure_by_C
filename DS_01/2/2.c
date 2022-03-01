// 메모리 동적 할당과 해제에 대해, 보다 견고한 할당이 될 수 있따록 매크로를 사용하여 다시 작성하여 출력하세요

#define MALLOC(p,s)  \
	if (!((p) = malloc(s))){  \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}\

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i, * pi;
	float f, * pf;

	MALLOC(pi, sizeof(int));
	MALLOC(pf, sizeof(float));

	*pi = 1024;
	*pf = 3.14;

	printf("an integer = %d, a float = %f \n", *pi, *pf);
	free(pi);
	free(pf);

	return 0;
}