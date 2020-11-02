#include<stdio.h>

int main() {
    bool printed = false;
    for (int i = 0; i <= 20; i++) {
        for(int j = 0; j < 33;j ++) {
            int k = 100 - i - j;
            if (k % 3 == 0 && (i * 5 + j * 3 + k / 3 == 100)) {
                if (!printed) {
                    printed = true;
                    printf("%d", i);
                    printf(",%d,%d", j, k);
                }
                else printf(",%d,%d,%d", i, j, k);
            }
        }
    }
    printf("\n");
    return 0;
}
