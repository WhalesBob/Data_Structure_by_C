/*
5. �� ���� ��Ʈ�� string, pat�� ���� ��, pat�� string�� Ž���ϱ� ���� �����̴�. string
�ȿ� pat�� �ִ��� ã�Ƴ��� ���� pat ���� ��ġ ������ �̿��Ͽ� ��� Ž���� ����ؾ�
���� ���� �ϴ� ���α׷��� �ۼ��Ͻÿ�. (program 2.14�� ����)
string�� pat ���� Ű����� �Է� �ް��ϰ�, ���� ��Ī�� ���� �ۼ��� pat�� ��ġ ���� ��
(failure �迭 ��)�� pat�� string�ȿ� �ִٸ� ���� ��ġ�� ����Ͻÿ�. (��, ������ġ 0����
���)
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

    printf("���ڿ��� �Է��ϼ��� : ");
    scanf_s("%s", string, sizeof(string));
    fflush(stdin);
    printf("���� ������ �Է��ϼ��� : ");
    scanf_s("%s", pat, sizeof(pat)); // �Է� ���� ���� ����

    fail(pat); // ���� ��� �� ����.
    printf("pat�� ��ġ ���� �� \n");
    for (int i = 0; i < strlen(pat); i++) {
        printf("failure[%d]= %3d  ",i,failure[i]);
        if (i % 5 == 4) {
            printf("\n");
        }
    }
    printf("\n");

    int n = pmatch(string, pat);
    if (n == -1) {
        printf("���� ���ڿ��� ���� ���ڿ��� ���Ե��� ����.");
    }
    else {
        printf("���ڿ� %d ��°���� ������ ���۵�.",n);
    }

	return 0;
}
int pmatch(char* string, char* pat) {
    int i=0, j=0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    while (i < lens && j < lenp) { // i�� string index, j�� pattern�� index
        if (string[i] == pat[j]) { // string�� i�� pattern�� j�� ���ٸ�, 
            i++; j++; // ���� ����.
        }
        else if (j == 0) { // ���κп��� �ƿ� ó������ ���� �ʾҴٸ�
            i++; //i�� �������Ѽ� �ٽ� ��, ������ pattern�� ù �κа� �¾ƾ� ��.
        }
        else {          // �߰��� Ʋ���� ���, 
            j = failure[j - 1] + 1; // j�� failure[j-1] ���� 1 ����? ���� �κп��� failure�� �ǵ��. 
        } // �߰��� Ʋ���� ��쿡�� �ǵ��. 
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