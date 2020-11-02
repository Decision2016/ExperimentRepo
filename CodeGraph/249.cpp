#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n / 10000 == 0 || n / 10000 >= 10) {
        printf("error\n");
        return 0;
    }
    if (n / 10000 == n % 10 && (n / 1000) % 10 == (n % 100) / 10) printf("Yes\n");
    else printf("No\n");
    return 0;
}
