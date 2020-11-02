#include <stdio.h>

double x, n, e = 1.0, tmp = 1.0;

int main() {
    scanf("%lf %lf", &x, &n);

    if (n < 0) printf("error\n");

    for (int i = 1; i <= n; i++) {
        tmp =  tmp * x / i;
        e += tmp;
    }

    printf("%.6lf", e);
    return 0;
}
