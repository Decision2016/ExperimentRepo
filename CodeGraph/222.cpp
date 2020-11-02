#include<stdio.h>
#include<string.h>

char s1[1000], s2[1000];

int main() {
    scanf("%s %s", s1, s2);
    int len = strlen(s1);

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            printf("%d\n", s1[i] - s2[i]);
            break;
        }
    }
    return 0;
}
