#include<stdio.h>
#include<math.h>

bool check(int num) {
    int div = sqrt(double(num));
    for (int i = 2;i <= div; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int n, half;
    scanf("%d", &n);

    if (n % 2 != 0) {
        printf("Error\n");
        return 0;
    }
    half = n / 2;

    for(int i = 2; i < half; i++) {
        if (check(i) && check(n - i)) {
            printf("%d+%d\n",i, n - i);
        }
    }
    return 0;
}
