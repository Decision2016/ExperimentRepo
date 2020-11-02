#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n % 2 == 0 || n <= 0) {
        printf("error\n");
        return 0;
    }

    int space = n / 2 + 1;
    for (int i = 1;i <= space; i++) {
        for (int j = 1; j <= space - i; j++) printf(" ");
        for (int j = 1; j <= i * 2 - 1;j++) printf("*");
        printf("\n");
    }
    return 0;
}
