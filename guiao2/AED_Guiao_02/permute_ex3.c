#include <stdio.h>

void Permute(int* a, int* b, int* c) {
    int temp = *a;
    *a = *c;
    *c = *b;
    *b = temp;
}

int main() {
    int num1 = 10, num2 = 20, num3 = 30;

    printf("Valores antes da permutação:\n");
    printf("num1: %d, num2: %d, num3: %d\n", num1, num2, num3);

    Permute(&num1, &num2, &num3);

    printf("Valores após a permutação circular:\n");
    printf("num1: %d, num2: %d, num3: %d\n", num1, num2, num3);

    return 0;
}
