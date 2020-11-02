#include<stdio.h>

int a[11], sum = 1;

int main() {
    a[10] = 1;
    for (int i = 9; i >= 1; i--) {
        a[i] = (a[i + 1] + 1) * 2;
        printf("%d,", a[i]);
    }
    printf("%d", a[1]);
    return 0;
}
