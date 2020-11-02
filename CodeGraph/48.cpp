#include <stdio.h>

int a[10];

void bub_sort() {
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (a[i] > a[j]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }

    bub_sort();

    for (int i = 0; i < 10; i++) {
        if (i == 0) printf("%d", a[i]);
        else {
            printf(",%d", a[i]);
        }
    }

    return 0;
}
