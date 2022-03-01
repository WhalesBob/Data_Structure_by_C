/*
4. �� ���� ��Ʈ�� string, pat�� ���� ��, pat�� string�� Ž���ϱ� ���� �����̴�. string
�ȿ� pat�� �ִ��� ã�Ƴ��� ���� pat�� ������ ���ڸ� ���� �˻��ϴ� ���α׷��� �ۼ��Ͻ�
��. (program 2.13�� ����)
string�� pat ���� Ű����� �Է� �ް��ϰ�, pat�� string�ȿ� �ִٸ� ���� ��ġ�� ����Ͻ�
��. (��, ������ġ 0���� ���)
*/

#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat);

int main(void) {

    char string[1000];
    char pat[1000];

    printf("���ڿ��� �Է��ϼ��� : ");
    scanf_s("%s", string, sizeof(string));
    printf("���� ������ �Է��ϼ��� : ");
    scanf_s("%s", pat, sizeof(pat)); // �Է� ���� ���� ����

    int n = nfind(string, pat);
    if (n == -1) {
        printf("���ϰ� ��ġ�ϴ� �κ��� ����");
    }
    else {
        printf("���ڿ� %d ��°���� ������ ���۵�..", n);
    }

    return 0;
}
int nfind(char* string, char* pat) {
    int start = 0, j = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;

    int endmatch = lastp;

    for (int i = 0; endmatch <= lasts; endmatch++, start++) {  // endmatch,start  �Ѵ� string�� ���� ��.
        if (string[endmatch] == pat[lastp]) { // �翬�ϰԵ�, lastp �� ������ ����
            for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++); // j�� patten����, i�� start�������� ��. j �� �翬�� lastp �ٷ� ��ĭ���� ���ϸ� �ǰ�, �ΰ��� ������ ����.
        }
        if (j == lastp) {
            return start;
        }
    }
    return -1;
}