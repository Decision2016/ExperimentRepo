#include<stdio.h>

int main() {
    double pi = 4.0;
    int n;

    scanf("%d", &n);
    double tmp = -1.0;
    for (int i = 1; i < n; i++) {
        pi += 4.0 * tmp / (i * 2 + 1);
        tmp *= -1.0;
    }
    printf("%.2lf", pi);
    return 0;
}
