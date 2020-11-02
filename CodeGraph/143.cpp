#include<stdio.h>
#include<string.h>

int main() {
    char s[1000];
    int cnt1 = 0, cnt2 = 0;
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'a') cnt1++;
        else if(s[i] == 'd') cnt2++;
    }
    printf("a:%d,d:%d", cnt1, cnt2);
    return 0;
}
