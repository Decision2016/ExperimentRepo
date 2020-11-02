#include<stdio.h>
int n;
bool all[100000];

void euler() {
    if (n <= 1) {printf("error\n"); return ;}
    for (int i = 1; i <= n; i++) all[i] = true;
    for (int i = 2; i <= n; i++) {
        if (all[i]) {
            printf("%d,", i);
            for (int j = i * 2; j <= n; j += i) all[j] = false;
        }
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    euler();
    return 0;
}
