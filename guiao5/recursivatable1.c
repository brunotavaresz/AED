#include <stdio.h>

int count1 = 0;

int firstFunction(int n) {
    count1++;
    if (n == 1) {
        return 1;
    } else {
        return firstFunction(n / 2) + n;
    }
}

int main() {
    int N;
    printf("N\t1ª Função (N)\tNº de Chamadas\n");
    for (N = 1; N <= 15; N++) {
        count1 = 0;
        int result = firstFunction(N);
        printf("%d\t%d\t%d\n", N, result, count1);
    }
    return 0;
}
