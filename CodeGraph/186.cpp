#include<stdio.h>

int main() {
    double ans = 0.0;
    int cnt = 0, tmp = 2, day = 1;

    while (true) {
        cnt += tmp;
        tmp *= 2;

        if (cnt + tmp > 100) break;
        day++;
    }

    ans = cnt * 0.8 / day;
    printf("%.2lf\n", ans);
    return 0;
}
