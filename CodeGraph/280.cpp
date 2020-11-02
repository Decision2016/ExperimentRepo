#include <stdio.h>

const float pi = 3.14;

int main() {
    float r, h, area, volume;

    scanf("%f %f",&r, &h);
    area = pi * r * r;
    volume = area * h;

    printf("area=%.2f,volume=%.2f\n", area, volume);

    return 0;
}
