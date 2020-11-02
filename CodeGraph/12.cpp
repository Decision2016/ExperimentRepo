#include<stdio.h>

int main() {
    int a, b, c;

    scanf("%d,%d,%d", &a, &b, &c);

    if (a <=0 || b <= 0 || c <= 0) {
        printf("error\n");
        return 0;
    }

    if (a + b > c) printf("yes\n");
    else printf("no\n");
    return 0;
}
