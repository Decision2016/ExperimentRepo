#include <stdio.h>
#include <math.h>

int n;

int main() {
    scanf("%d", &n);

    int div = sqrt(double(n));

    for (int i = 2; i <= div; i++) {
        if (n % i == 0) {
            printf("no\n");
            return 0;
        }
        else continue;
    }
    printf("yes\n");
    return 0;
}
