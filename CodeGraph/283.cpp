#include<stdio.h>

struct node {
    int data;
    struct node *next;
}*header;

int main(int data[],int n) {
    if (data == NULL) {
        printf("error\n");
        return (int)NULL;
    }

    header = new node;
    header -> next = NULL;
    struct node *now = header;

    for (int i = 0; i < n; i++) {
        struct node *p = new node;
        p -> data = data[i];
        p -> next = NULL;
        now -> next = p;
        now = now -> next;
    }
    return (int)header;
}


int main() {
    struct node *res;
    int array[] = {122, 442, 333};
    printf("%d\n", res);
    while (res != NULL) {
        printf("%d\n", res->data);
        res = res -> next;
    }
    return 0;
}
