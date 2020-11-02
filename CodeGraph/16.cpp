#include<stdio.h>

int main() {
    float now = 2.0, ans = 0.0, eps;

    scanf("%f", &eps);

    for (int i = 1; ;i++) {
        if (i != 1) now = now * (i - 1) / (2 * i - 1);
        ans += now;
        if (now < eps) break;
    }
    printf("%.6f\n", ans);
    return 0;
}
