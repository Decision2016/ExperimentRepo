#include<stdio.h>
#include<math.h>


bool check(int number) {
    int div = sqrt(double(number));
    int sum = 1;
    for (int i = 2; i <= div; i++) {
        if (number % i == 0) {
            sum += (i + number / i);
        }
    }
    // printf("%d %d\n", sum, number);
    if (sum == number) return true;
    return false;
}

int main() {
    for (int i = 1; i <= 1000; i++) {
        if (check(i)) printf("%d\n", i);
    }
    return 0;
}
