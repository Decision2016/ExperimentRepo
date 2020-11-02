#include<stdio.h>

int a = 1, b = 1, n;

int main() {
    scanf("%d", &n);
    if (n <= 2) printf("1\n");
    else {
        for (int i = 1; i <= n - 2; i++) {
            int tmp = a + b;
            a = b;
            b = tmp;
        }
        printf("%d\n", b);
    }
    return 0;
}
