#include<stdio.h>
#include<string.h>

char s[300];
int cnt = 0;
bool flag = false;

int main() {
    gets(s);
    int len = strlen(s);
    if (s[0] != ' ') flag = true;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') flag = true;
        else if (s[i] != '\n' && flag) {
            flag = false;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
