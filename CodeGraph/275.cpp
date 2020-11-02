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

    if (n % 2 == 1 || n < 4 || n > 2000) {
        printf("error\n");
        return 0;
    }
    half = n / 2;

    for(int i = 2; i <= half; i++) {
        if (check(i) && check(n - i)) {
            printf("%d %d\n",i, n - i);
            break;
        }
    }
    return 0;
}
