#include<stdio.h>
#include<stdlib.h>

void run() {
    int n;
    scanf ("%d", &n);
    int *a = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) a[i] ^= a[j] ^= a[i] ^= a[j];
        }
    }
    printf("%d", a[0]);
    for (int i = 1; i < n; i++) printf(",%d", a[i]);
    printf("\n");
}

int main() {
    run();
    return 0;
}
