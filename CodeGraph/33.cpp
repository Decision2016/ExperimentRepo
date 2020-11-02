#include<stdio.h>
#include<string.h>

void my_strcpy(char *destination, char *source) {
    if (destination == NULL || source == NULL) {
		printf("error");
		return ;
    }
    int position = 0;
    while (source[position] != ' ') {
        destination[position] = source[position];
        position ++;
    }
    destination[position] = '\0';
}

int main() {
    char s1[100], s2[200];
    my_strcpy(s2, "1 2");
    printf("%s\n", s2);
    return 0;
}
