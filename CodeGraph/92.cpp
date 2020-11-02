#include<stdio.h>

int main() {
    unsigned int k = 0, m, tmp = 1;
    scanf("%u", &m);
    while (tmp <= m && k <= 31) {
        tmp <<= 1;
        k ++;
    }
    if (tmp > m || k == 32) k --;
    printf("%u\n", k);
    return 0;
}
