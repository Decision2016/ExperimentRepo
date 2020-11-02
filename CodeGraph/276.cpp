#include<stdio.h>

int n;
int a[200], b[200], t[200], M = 1, ans;

void exgcd(int _a, int _b, int &d, int &x, int &y) {
    if (_b == 0) {
        x = 1;
        y = 0;
        d = _a;
        return ;
    }
    exgcd(_b, _a % _b, d, y, x);
    y -= _a / _b * x;
}

int main() {
    scanf("%d", &n);
    if (n == 0) {
        printf("error\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        M = M * a[i];
        if (a[i] <= 0 || b[i] <= 0) {
            printf("error\n");
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        int now = M / a[i], x, y, d;
        exgcd(now, a[i], d, x, y);
        x = (x + a[i]) % a[i];
        ans = (ans + b[i] * x * now) % M;
    }
    printf("%d\n",ans);
    return 0;
}
