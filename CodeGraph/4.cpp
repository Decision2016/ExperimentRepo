#include <stdio.h>

int main() {
    int n;
    int result;

    scanf("%d", &n);
    printf("%d", n);
    result = n;
    for (int i = 1;i < 5; i++) {
        result = result * n;
        printf(" %d", result);
    }
    printf("\n");
    return 0;
}
