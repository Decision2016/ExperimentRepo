#include <stdio.h>

int n;

int main() {
    scanf("%d", &n);

    if (n > 10 || n < 1) {
        printf("error\n");
        return 0;
    }

    int res = 0, tmp = 1;
    for (int i = 1; i <= n; i++) {
        tmp = tmp * i;
        res += tmp;
    }
    printf("%d\n", res);

    return 0;
}
