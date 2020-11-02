#include<stdio.h>

bool isLeap(int _year) {
    if ((_year % 100 != 0 && _year % 4 == 0) || _year % 400 == 0) return true;
    return false;
}

int main() {
    int year, month;
    scanf("%d %d", &year, &month);
    if (month > 12) month %= 12;
    if (month == 2) {
        if (isLeap(year)) printf("days:29\n");
        else printf("days:28\n");
    }
    else if (month == 4 || month == 6 || month == 9 || month ==11) printf("days:30\n");
    else printf("days:31\n");

    return 0;
}
