#include <stdio.h>

int recursiveFunction1(int n, int *count) {
    (*count)++;  // Contador de chamadas recursivas
    if (n <= 1) {
        return 1;
    }
    int m = n / 2;
    return recursiveFunction1(m, count) + n;
}

int main() {
    int n = 10; // Substitua pelo valor desejado
    int count = 0; // Inicializa o contador
    int result = recursiveFunction1(n, &count);
    printf("Resultado: %d\n", result);
    printf("Número de chamadas recursivas: %d\n", count);
    return 0;
}
