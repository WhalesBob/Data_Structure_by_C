/*
5. 두 개의 스트링 string, pat가 있을 때, pat는 string을 탐색하기 위한 패턴이다. string
안에 pat가 있는지 찾아내기 위해 pat 내의 위치 정보를 이용하여 어디서 탐색을 계속해야
할지 결정 하는 프로그램을 작성하시오. (program 2.14를 참조)
string과 pat 값은 키보드로 입력 받게하고, 패턴 매칭을 위해 작성한 pat의 위치 정보 값
(failure 배열 값)과 pat가 string안에 있다면 시작 위치를 출력하시오. (단, 시작위치 0부터
출발)
*/

#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100

int pmatch(char* string, char* pat);
void fail(char* pat);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pattern[MAX_PATTERN_SIZE];

int main(void) {

    char string[1000];
    char pat[1000];

    printf("문자열을 입력하세요 : ");
    scanf_s("%s", string, sizeof(string));
    fflush(stdin);
    printf("비교할 패턴을 입력하세요 : ");
    scanf_s("%s", pat, sizeof(pat)); // 입력 들어가는 것은 성공

    fail(pat); // 실패 행렬 싹 구현.
    printf("pat의 위치 정보 값 \n");
    for (int i = 0; i < strlen(pat); i++) {
        printf("failure[%d]= %3d  ",i,failure[i]);
        if (i % 5 == 4) {
            printf("\n");
        }
    }
    printf("\n");

    int n = pmatch(string, pat);
    if (n == -1) {
        printf("패턴 문자열이 위의 문자열에 포함되지 않음.");
    }
    else {
        printf("문자열 %d 번째부터 패턴이 시작됨.",n);
    }

	return 0;
}
int pmatch(char* string, char* pat) {
    int i=0, j=0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    while (i < lens && j < lenp) { // i가 string index, j가 pattern의 index
        if (string[i] == pat[j]) { // string의 i와 pattern의 j가 같다면, 
            i++; j++; // 같이 증가.
        }
        else if (j == 0) { // 윗부분에서 아예 처음부터 맞지 않았다면
            i++; //i만 증가시켜서 다시 비교, 어차피 pattern의 첫 부분과 맞아야 함.
        }
        else {          // 중간에 틀리는 경우, 
            j = failure[j - 1] + 1; // j는 failure[j-1] 에서 1 증가? 여기 부분에서 failure를 건든다. 
        } // 중간에 틀리는 경우에만 건든다. 
    }
    return ((j == lenp) ? (i - lenp) : -1);
}
void fail(char* pat) {
    int n = strlen(pat);
    failure[0] = -1;
    for (int j = 1; j < n; j++) {
        int i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0)) {
            i = failure[i];
        }
        if (pat[j] == pat[i + 1]) {
            failure[j] = i + 1;
        }
        else {
            failure[j] = -1;
        }
    }
}