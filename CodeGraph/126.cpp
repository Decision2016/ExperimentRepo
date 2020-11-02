#include<stdio.h>

int main() {
    int n, res = 1, tmp = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        res = res * i;
        tmp = i;
        if (i == 12) break;
    }
    printf("%d!=%d\n", tmp, res);
    return 0;
}
