#include <stdio.h>

char c, op;

double result, a, b;


int main() {
    while (true) {
        scanf("%lf %c %lf", &a, &op, &b);
        getchar();

        bool error = false;
        if (op == '+') result = a + b;
        else if (op == '-') result = a - b;
        else if (op == '*') result = a * b;
        else if (op == '/') {
            if (b != 0.0) result = a / b;
            else error = true;
        }
        else error = true;

        if(!error) printf("%.2lf %c %.2lf = %.2lf\n", a, op, b, result);
        else printf("error\n");

        scanf("%c", &c);
        if (c == 'n') break;
    }
    return 0;
}
