#include<stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b, d;
    scanf("%d %d", &a, &b);

    if (a >= b) d = gcd(a, b);
    else d = gcd(b, a);

    printf("%d\n",a * b / d);
    return 0;
}
