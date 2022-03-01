/*
2. Program 3.12 Maze search function을 사용하는 미로탐색 프로그램을 작성하여라. 미로에 대한 정보는 input.txt에 있다. 
input.txt의 첫 번째 줄은 미로의 행과 열의 크기를 나타내며, 다음 행부터는 미로 길에 대한 정보를 나타낸다.
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#define MAX_STACK_SIZE 100

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int vertical;
	int horizental;
}offsets;

typedef struct {
	int row;
	int col;
	int dir;
}element;

offsets move[8];
element stack[MAX_STACK_SIZE];

int top = -1;
FILE* fp = NULL;

void setMove(void);
int** makeMaze(rows, cols);
int** makeMarks(rows, cols);
void stackFull(void);
void stackEmpty(void);
void push(element item);
element pop(void);

int main(void) {

	setMove();
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open this file");
		exit(EXIT_FAILURE);
	}

	int** maze; int** mark;
	int inputRows, inputCols;
	int row,col, nextRow, nextCol, dir, found = 0;
	element position;

	fscanf_s(fp, "%d %d\n", &inputRows, &inputCols);
	maze = makeMaze(inputRows, inputCols);  // 잘 받았음. 1벽도 포함.
	mark = makeMarks(inputRows, inputCols); // Maze, Mark 둘 다 잘 만들어졌음.

	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vertical;
			nextCol = col + move[dir].horizental;
			if (nextRow == inputRows && nextCol == inputCols) { // 찾았을 때
				found = 1;
			}
			else if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol]){ // mark에서도 안가고, maze에서도 길 있을때
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else {
				dir++;
			}
		}
	}
	if (found) {
		printf("The path is : \n");
		printf("row col \n");
		for (int i = 0; i <= top; i++) {
			printf("%2d %4d \n", stack[i].row, stack[i].col);
		}
		printf("%2d %4d \n", row, col);
		printf("%2d %4d \n", inputRows, inputCols);
	}
	else {
		printf("The name does not have a path \n");
	}

	free(mark);
	free(maze);

	return 0;
}
void setMove(void) {

	move[0].vertical = -1; move[0].horizental = 0; // N
	move[1].vertical = -1; move[1].horizental = 1; // NE
	move[2].vertical = 0;  move[2].horizental = 1; // E
	move[3].vertical = 1;  move[3].horizental = 1; // SE
	move[4].vertical = 1;  move[4].horizental = 0; // S
	move[5].vertical = 1;  move[5].horizental = -1;// SW
	move[6].vertical = 0;  move[6].horizental = -1;// W
	move[7].vertical = -1; move[7].horizental = -1;// NW

	return;
}
int** makeMaze(rows, cols) {
	int** x;
	MALLOC(x, (rows+2) * sizeof(*x));

	for (int i = 0; i < rows + 2; i++) {
		MALLOC(x[i], (cols+2) * sizeof(**x));
	}

	for (int i = 0; i < rows + 2; i++) {
		for (int j = 0; j < cols + 2; j++) {
			x[i][j] = 1;
		}
	}

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			fscanf_s(fp, "%d ", &x[i][j]);
		}
	}
	return x;
}
int** makeMarks(rows, cols) {
	int** x;
	MALLOC(x, (rows + 2) * sizeof(*x));

	for (int i = 0; i < rows + 2; i++) {
		MALLOC(x[i], (cols + 2) * sizeof(**x));
	}

	for (int i = 0; i < rows + 2; i++) {
		for (int j = 0; j < cols + 2; j++) {
			x[i][j] = 1;
		}
	}

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			x[i][j] = 0;
		}
	}
	return x;
}
void stackFull(void) {
	fprintf(stderr, "stack is full, cannot add element\n");
	exit(EXIT_FAILURE);
}
void stackEmpty(void) {
	fprintf(stderr, "stack is empty, cannot show element to you\n");
	exit(EXIT_FAILURE);
}
void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top] = item;
}
element pop(void) {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}
