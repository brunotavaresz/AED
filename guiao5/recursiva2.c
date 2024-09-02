#include <stdio.h>

int recursiveFunction2(int n, int *count) {
    (*count)++;  // Contador de chamadas recursivas
    if (n <= 1) {
        return 1;
    }
    int m1 = n / 2;
    int m2 = (n + 1) / 2;
    return recursiveFunction2(m1, count) + recursiveFunction2(m2, count) + n;
}

int main() {
    int n = 10; // Substitua pelo valor desejado
    int count = 0; // Inicializa o contador
    int result = recursiveFunction2(n, &count);
    printf("Resultado: %d\n", result);
    printf("Número de chamadas recursivas: %d\n", count);
    return 0;
}
