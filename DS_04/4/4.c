#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat);

int main(void) {

    char string[1000];
    char pat[1000];

    printf("문자열을 입력하세요 : ");
    scanf_s("%s", string, sizeof(string));
    printf("비교할 패턴을 입력하세요 : ");
    scanf_s("%s", pat, sizeof(pat)); // 입력 들어가는 것은 성공

    int n = nfind(string, pat);
    if (n == -1) {
        printf("패턴과 일치하는 부분이 없음");
    }
    else {
        printf("문자열 %d 번째부터 패턴이 시작됨..", n);
    }

    return 0;
}
int nfind(char* string, char* pat) {
    int start = 0, j = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;

    int endmatch = lastp;

    for (int i = 0; endmatch <= lasts; endmatch++, start++) {  // endmatch,start  둘다 string에 들어가는 것.
        if (string[endmatch] == pat[lastp]) { // 당연하게도, lastp 는 가만히 있지
            for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++); // j는 patten에서, i는 start지점부터 비교. j 는 당연히 lastp 바로 앞칸까지 비교하면 되고, 두개가 같으면 되지.
        }
        if (j == lastp) {
            return start;
        }
    }
    return -1;
}