#include<stdio.h>

int main() {
    unsigned int a;
    int  b, ans;
    scanf("%d %d", &a, &b);

    if (b > 0) ans = (a << b) | (a >> (32 - b));
    else {
        b = -b;
        ans = (a >> b) | (a << (32 - b));
    }
    printf("%d\n", ans);
    return 0;
}
