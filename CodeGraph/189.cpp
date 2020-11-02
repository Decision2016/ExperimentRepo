#include<stdio.h>

int a[101], n, pos;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &pos);

    int l = 1, r = n, mid, ans;

    while (l <= r) {
        mid = (l + r) >> 1;
        if (a[mid] < pos) l = mid + 1;
        else {
            r = mid - 1;
        }
        ans = mid;
    }

    printf("%d\n", ans);
    return 0;
}
