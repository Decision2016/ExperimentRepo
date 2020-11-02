#include<stdio.h>
#include<string.h>

char word[100];
bool error = false;

int main() {
    scanf("%s", word);

    int len = strlen(word);
    if(len > 20) len = 20;
    if(len == 0) error = true;

    for (int i = 0; i < len; i++) {
        if (word[i] <= 'Z' && word[i] >= 'A') {
            word[i] = 'A' + (word[i] - 'A' + 4) % 26;
        }
        else if (word[i] <= 'z' && word[i] >= 'a') {
            word[i] = 'a' + (word[i] - 'a' + 4) % 26;
        }
        else {
            error = true;
        }
        if (error) break;
    }
    if (error) printf("error\n");
    else {
        for (int i = 0; i < len; i++) printf("%c", word[i]);
        printf("\n");
    }
    return 0;
}
