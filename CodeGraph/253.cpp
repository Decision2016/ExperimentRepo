#include<stdio.h>
#include<string.h>

char s[100];
int ans = 0;

int main() {
    scanf("%s", s);
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        ans <<= 1;
        if (s[i] == '1') ans |= 1;
    }
    printf("%d\n", ans);
    return 0;
}
